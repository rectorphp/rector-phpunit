<?php

declare(strict_types=1);

namespace Rector\PHPUnit\CodeQuality\Rector\ClassMethod;

use PhpParser\Node;
use PhpParser\Node\Arg;
use PhpParser\Node\ClosureUse;
use PhpParser\Node\Expr\Assign;
use PhpParser\Node\Expr\CallLike;
use PhpParser\Node\Expr\MethodCall;
use PhpParser\Node\Expr\New_;
use PhpParser\Node\Expr\StaticCall;
use PhpParser\Node\Expr\Variable;
use PhpParser\Node\Stmt;
use PhpParser\Node\Stmt\ClassMethod;
use PhpParser\Node\Stmt\Expression;
use PhpParser\Node\Stmt\Foreach_;
use Rector\PhpParser\Node\BetterNodeFinder;
use Rector\PHPUnit\CodeQuality\NodeAnalyser\AssertMethodAnalyzer;
use Rector\PHPUnit\CodeQuality\NodeAnalyser\AssignedMocksCollector;
use Rector\PHPUnit\CodeQuality\NodeFinder\VariableFinder;
use Rector\PHPUnit\NodeAnalyzer\TestsNodeAnalyzer;
use Rector\Rector\AbstractRector;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;

/**
 * @see \Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\BareCreateMockAssignToDirectUseRector\BareCreateMockAssignToDirectUseRectorTest
 */
final class BareCreateMockAssignToDirectUseRector extends AbstractRector
{
    public function __construct(
        private readonly TestsNodeAnalyzer $testsNodeAnalyzer,
        private readonly AssignedMocksCollector $assignedMocksCollector,
        private readonly BetterNodeFinder $betterNodeFinder,
        private readonly VariableFinder $variableFinder,
        private readonly AssertMethodAnalyzer $assertMethodAnalyzer,
    ) {
    }

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition(
            'Add explicit instance assert between above nullable object pass',
            [
                new CodeSample(
                    <<<'CODE_SAMPLE'
use PHPUnit\Framework\TestCase;

final class SomeTest extends TestCase
{
    public function test()
    {
        $someObject = $this->createMock(SomeClass::class);
        $this->process($someObject);
    }


    private function process(SomeClass $someObject): void
    {
    }
}
CODE_SAMPLE

                    ,
                    <<<'CODE_SAMPLE'
use PHPUnit\Framework\TestCase;

final class SomeTest extends TestCase
{
    public function test()
    {
        $this->process($this->createMock(SomeClass::class));
    }

    private function process(SomeClass $someObject): void
    {
    }
}
CODE_SAMPLE
                ),
            ]
        );
    }

    /**
     * @return array<class-string<Node>>
     */
    public function getNodeTypes(): array
    {
        return [ClassMethod::class, Foreach_::class];
    }

    /**
     * @param ClassMethod|Foreach_ $node
     */
    public function refactor(Node $node): ?Node
    {
        if (! $this->testsNodeAnalyzer->isInTestClass($node)) {
            return null;
        }

        if ($node->stmts === null || count($node->stmts) < 2) {
            return null;
        }

        $mockedClassesToVariableNames = $this->assignedMocksCollector->collect($node);
        if ($mockedClassesToVariableNames === []) {
            return null;
        }

        $hasChanged = false;

        foreach (array_keys($mockedClassesToVariableNames) as $variableName) {
            // variable cannot be part of any method call
            if ($this->isVariableUsedAsPartOfMethodCall($node, $variableName)) {
                continue;
            }

            if ($this->isUsedMoreOftenThanInCallLikeArgs($node, $variableName)) {
                continue;
            }

            if ($this->isUsedInClosure($node, $variableName)) {
                continue;
            }

            if ($this->isUsedInAssertCall($node, $variableName)) {
                continue;
            }

            // 1. remove initial assign
            $variablesToMethodCalls = [];

            foreach ($node->stmts as $key => $stmt) {
                if ($stmt instanceof Expression && $stmt->expr instanceof Assign) {
                    $assign = $stmt->expr;

                    $instanceArg = $this->assignedMocksCollector->matchCreateMockArgAssignedToVariable($assign);
                    if ($instanceArg instanceof Arg && $assign->var instanceof Variable && $this->isName(
                        $assign->var,
                        $variableName
                    )) {
                        // 1. remove assign
                        unset($node->stmts[$key]);
                        $hasChanged = true;
                        $variablesToMethodCalls[$variableName] = $assign->expr;
                        continue;
                    }
                }

                // nothing to processy yet
                if ($variablesToMethodCalls === []) {
                    continue;
                }

                // 2. replace variable with call-like args of new instance
                /** @var CallLike[] $callLikes */
                $callLikes = $this->findCallLikes($stmt);

                foreach ($callLikes as $callLike) {
                    foreach ($callLike->getArgs() as $arg) {
                        if (! $arg->value instanceof Variable) {
                            continue;
                        }

                        if (! $this->isName($arg->value, $variableName)) {
                            continue;
                        }

                        if (! isset($variablesToMethodCalls[$variableName])) {
                            continue;
                        }

                        // 2. replace variable with call-like args
                        $arg->value = $variablesToMethodCalls[$variableName];
                    }
                }
            }
        }

        if (! $hasChanged) {
            return null;
        }

        return $node;
    }

    private function isVariableUsedAsPartOfMethodCall(ClassMethod|Foreach_ $stmtsAware, string $variableName): bool
    {
        /** @var MethodCall[] $methodCalls */
        $methodCalls = $this->betterNodeFinder->findInstancesOfScoped([$stmtsAware], [MethodCall::class]);

        foreach ($methodCalls as $methodCall) {
            if ($this->isName($methodCall->var, $variableName)) {
                return true;
            }
        }

        return false;
    }

    private function isUsedMoreOftenThanInCallLikeArgs(ClassMethod|Foreach_ $stmtsAware, string $variableName): bool
    {
        // get use count
        $foundVariables = $this->variableFinder->find($stmtsAware, $variableName);

        // found method call, static call or new arg-only usage
        $callLikeVariableUseCount = 0;

        /** @var CallLike[] $callLikes */
        $callLikes = $this->findCallLikes($stmtsAware);

        foreach ($callLikes as $callLike) {
            foreach ($callLike->getArgs() as $arg) {
                if (! $arg->value instanceof Variable) {
                    continue;
                }

                if (! $this->isName($arg->value, $variableName)) {
                    continue;
                }

                ++$callLikeVariableUseCount;
            }
        }

        // not suitable for direct replacing
        return (count($foundVariables) - 1) > ($callLikeVariableUseCount);
    }

    /**
     * @return CallLike[]
     */
    private function findCallLikes(ClassMethod|Foreach_|Stmt $node): array
    {
        $callLikes = $this->betterNodeFinder->findInstancesOfScoped(
            [$node],
            [MethodCall::class, StaticCall::class, New_::class]
        );

        return array_filter($callLikes, fn (CallLike $callLike): bool => ! $callLike->isFirstClassCallable());
    }

    private function isUsedInClosure(ClassMethod|Foreach_ $stmtsAware, string $variableName): bool
    {
        /** @var Node\ClosureUse[] $uses */
        $uses = $this->betterNodeFinder->findInstancesOf([$stmtsAware], [ClosureUse::class]);

        foreach ($uses as $use) {
            if ($this->isName($use->var, $variableName)) {
                return true;
            }
        }

        return false;
    }

    private function isUsedInAssertCall(ClassMethod|Foreach_ $stmtsAware, string $variableName): bool
    {
        /** @var StaticCall[]|MethodCall[] $calls */
        $calls = $this->betterNodeFinder->findInstancesOfScoped([$stmtsAware], [MethodCall::class, StaticCall::class]);

        $assertCalls = [];
        foreach ($calls as $call) {
            if (! $this->assertMethodAnalyzer->detectTestCaseCall($call)) {
                continue;
            }

            $assertCalls[] = $call;
        }

        foreach ($assertCalls as $assertCall) {
            foreach ($assertCall->getArgs() as $assertCallArg) {
                if (! $assertCallArg->value instanceof Variable) {
                    continue;
                }

                if ($this->isName($assertCallArg->value, $variableName)) {
                    return true;
                }

            }
        }

        return false;
    }
}
