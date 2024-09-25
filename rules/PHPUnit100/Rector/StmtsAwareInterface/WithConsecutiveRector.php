<?php

declare(strict_types=1);

namespace Rector\PHPUnit\PHPUnit100\Rector\StmtsAwareInterface;

use PhpParser\Node;
use PhpParser\Node\Arg;
use PhpParser\Node\Expr;
use PhpParser\Node\Expr\ArrayDimFetch;
use PhpParser\Node\Expr\Assign;
use PhpParser\Node\Expr\Closure;
use PhpParser\Node\Expr\Match_;
use PhpParser\Node\Expr\MethodCall;
use PhpParser\Node\Expr\StaticCall;
use PhpParser\Node\Expr\Variable;
use PhpParser\Node\Identifier;
use PhpParser\Node\MatchArm;
use PhpParser\Node\Param;
use PhpParser\Node\Scalar\LNumber;
use PhpParser\Node\Stmt;
use PhpParser\Node\Stmt\Expression;
use PhpParser\Node\Stmt\Return_;
use PhpParser\Node\Stmt\Throw_;
use Rector\Exception\ShouldNotHappenException;
use Rector\PhpParser\Node\BetterNodeFinder;
use Rector\PHPUnit\NodeAnalyzer\TestsNodeAnalyzer;
use Rector\PHPUnit\NodeFactory\WithConsecutiveMatchFactory;
use Rector\Rector\AbstractRector;
use Rector\ValueObject\PhpVersion;
use Rector\VersionBonding\Contract\MinPhpVersionInterface;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;

/**
 * @see \Rector\PHPUnit\Tests\PHPUnit100\Rector\StmtsAwareInterface\WithConsecutiveRector\WithConsecutiveRectorTest
 */
final class WithConsecutiveRector extends AbstractRector implements MinPhpVersionInterface
{
    /**
     * @var string
     */
    private const WITH_CONSECUTIVE_METHOD = 'withConsecutive';

    public function __construct(
        private readonly TestsNodeAnalyzer $testsNodeAnalyzer,
        private readonly BetterNodeFinder $betterNodeFinder,
        private readonly WithConsecutiveMatchFactory $withConsecutiveMatchFactory,
    ) {
    }

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition('Refactor deprecated withConsecutive() to willReturnCallback() structure', [
            new CodeSample(
                <<<'CODE_SAMPLE'
use PHPUnit\Framework\TestCase;

final class SomeTest extends TestCase
{
    public function run()
    {
        $this->personServiceMock->expects($this->exactly(2))
            ->method('prepare')
            ->withConsecutive(
                [1, 2],
                [3, 4],
            );
    }
}
CODE_SAMPLE

                ,
                <<<'CODE_SAMPLE'
use PHPUnit\Framework\TestCase;

final class SomeTest extends TestCase
{
    public function run()
    {
        $matcher = $this->exactly(2);

        $this->personServiceMock->expects($matcher)
            ->method('prepare')
            ->willReturnCallback(function ($parameters) use ($matcher) {
                match ($matcher->numberOfInvocations()) {
                    1 => self::assertEquals([1, 2], $parameters),
                    2 => self::assertEquals([3, 4], $parameters),
                };
            });
    }
}
CODE_SAMPLE
            ),
        ]);
    }

    /**
     * @return array<class-string<Node>>
     */
    public function getNodeTypes(): array
    {
        return [Expression::class];
    }

    /**
     * @param Expression $node
     */
    public function refactor(Node $node)
    {
        if (! $this->testsNodeAnalyzer->isInTestClass($node)) {
            return null;
        }

        $withConsecutiveMethodCall = $this->findMethodCall($node, self::WITH_CONSECUTIVE_METHOD);
        if (! $withConsecutiveMethodCall instanceof MethodCall) {
            return null;
        }

        if ($this->hasWillReturnMapOrWill($node)) {
            return null;
        }

        $returnStmts = [];
        $willReturn = $this->findMethodCall($node, 'willReturn');
        if ($willReturn instanceof MethodCall) {
            $args = $willReturn->getArgs();
            if (count($args) !== 1 || (! $args[0] instanceof Arg)) {
                return null;
            }

            $returnStmts = [new Return_($args[0]->value)];
        }

        $willReturnSelf = $this->findMethodCall($node, 'willReturnSelf');
        if ($willReturnSelf instanceof MethodCall) {
            if ($returnStmts !== []) {
                return null;
            }

            $selfVariable = $willReturnSelf;
            while (true) {
                if (! $selfVariable instanceof MethodCall) {
                    break;
                }

                $selfVariable = $selfVariable->var;
            }

            $returnStmts = [new Return_($selfVariable)];
        }

        $willReturnArgument = $this->findMethodCall($node, 'willReturnArgument');
        if ($willReturnArgument instanceof MethodCall) {
            if ($returnStmts !== []) {
                return null;
            }

            $parametersVariable = new Variable('parameters');

            $args = $willReturnArgument->getArgs();
            if (count($args) !== 1 || (! $args[0] instanceof Arg)) {
                return null;
            }

            $returnStmts = [new Return_(new ArrayDimFetch($parametersVariable, $args[0]->value))];
        }

        $willReturnOnConsecutiveCallsArgument = $this->findMethodCall($node, 'willReturnOnConsecutiveCalls');
        if ($willReturnOnConsecutiveCallsArgument instanceof MethodCall) {
            if ($returnStmts !== []) {
                return null;
            }

            $matcherVariable = new Variable('matcher');
            $numberOfInvocationsMethodCall = new MethodCall($matcherVariable, new Identifier('numberOfInvocations'));

            $matchArms = [];
            foreach ($willReturnOnConsecutiveCallsArgument->getArgs() as $key => $arg) {
                $matchArms[] = new MatchArm([new LNumber($key + 1)], $arg->value);
            }

            $returnStmts = [new Return_(new Match_($numberOfInvocationsMethodCall, $matchArms))];
        }

        $willReturnReferenceArgument = $this->findMethodCall($node, 'willReturnReference');
        $referenceVariable = null;
        if ($willReturnReferenceArgument instanceof MethodCall) {
            if ($returnStmts !== []) {
                return null;
            }

            $args = $willReturnReferenceArgument->args;
            if (count($args) !== 1 || (! $args[0] instanceof Arg)) {
                return null;
            }

            $referenceVariable = $args[0]->value;
            if (! $referenceVariable instanceof Variable) {
                return null;
            }

            $returnStmts = [new Return_($referenceVariable)];
        }

        $willThrowException = $this->findMethodCall($node, 'willThrowException');
        if ($willThrowException instanceof MethodCall) {
            if ($returnStmts !== []) {
                return null;
            }

            $args = $willThrowException->getArgs();
            if (count($args) !== 1 || (! $args[0] instanceof Arg)) {
                return null;
            }

            $returnStmts = [new Throw_($args[0]->value)];
        }

        $this->removeMethodCalls($node, [
            'willReturn',
            'willReturnArgument',
            'willReturnSelf',
            'willReturnOnConsecutiveCalls',
            'willReturnReference',
            'willThrowException',
        ]);

        $expectsCall = $this->matchAndRefactorExpectsMethodCall($node);

        if (! $expectsCall instanceof MethodCall && ! $expectsCall instanceof StaticCall) {
            // fallback to default by case count
            $lNumber = new LNumber(\count($withConsecutiveMethodCall->args));
            $expectsCall = new MethodCall(new Variable('this'), new Identifier('exactly'), [new Arg($lNumber)]);
        }

        // 2. does willReturnCallback() exist? just merge
        $existingWillReturnCallback = $this->findMethodCall($node, 'willReturnCallback');
        if ($existingWillReturnCallback instanceof MethodCall) {
            $callbackArg = $existingWillReturnCallback->getArgs()[0];

            if (! $callbackArg->value instanceof Closure) {
                throw new ShouldNotHappenException();
            }

            $callbackClosure = $callbackArg->value;

            $matcherVariable = new Variable('matcher');
            $parametersVariable = new Variable('parameters');

            $parametersMatch = $this->withConsecutiveMatchFactory->createParametersMatch(
                $matcherVariable,
                $withConsecutiveMethodCall,
                $parametersVariable
            );

            $callbackClosure->params[] = new Param($parametersVariable);
            $callbackClosure->stmts = array_merge([new Expression($parametersMatch)], $callbackClosure->stmts);

            $this->removeMethodCalls($node, [self::WITH_CONSECUTIVE_METHOD]);
            return [$node];
        }

        // 3. rename and replace withConsecutive()
        return $this->refactorToWillReturnCallback(
            $withConsecutiveMethodCall,
            $returnStmts,
            $referenceVariable,
            $expectsCall,
            $node
        );
    }

    public function provideMinPhpVersion(): int
    {
        /**
         * This rule just work for phpunit 10,
         * And as php 8.1 is the min version supported by phpunit 10, then we decided to let this version as minimum.
         *
         * You can see more detail in this issue: https://github.com/rectorphp/rector-phpunit/issues/272
         */
        return PhpVersion::PHP_81;
    }

    /**
     * Replace $this->expects(...)
     *
     * @param Expression<MethodCall> $expression
     */
    private function matchAndRefactorExpectsMethodCall(Expression $expression): MethodCall|StaticCall|null
    {
        /** @var MethodCall|StaticCall|null $exactlyCall */
        $exactlyCall = null;

        $this->traverseNodesWithCallable($expression, function (Node $node) use (&$exactlyCall): ?MethodCall {
            if (! $node instanceof MethodCall) {
                return null;
            }

            if (! $this->isName($node->name, 'expects')) {
                return null;
            }

            $firstArg = $node->getArgs()[0];
            if (! $firstArg->value instanceof MethodCall && ! $firstArg->value instanceof StaticCall) {
                return null;
            }

            $exactlyCall = $firstArg->value;

            $node->args = [new Arg(new Variable('matcher'))];

            return $node;
        });

        return $exactlyCall;
    }

    private function findMethodCall(Expression $expression, string $methodName): ?MethodCall
    {
        if (! $expression->expr instanceof MethodCall) {
            return null;
        }

        /** @var MethodCall|null $methodCall */
        $methodCall = $this->betterNodeFinder->findFirst($expression->expr, function (Node $node) use (
            $methodName
        ): bool {
            if (! $node instanceof MethodCall) {
                return false;
            }

            return $this->isName($node->name, $methodName);
        });
        return $methodCall;
    }

    private function hasWillReturnMapOrWill(Expression $expression): bool
    {
        $nodesWithWillReturnMap = $this->betterNodeFinder->find($expression, function (Node $node): bool {
            if (! $node instanceof MethodCall) {
                return false;
            }

            return $this->isNames($node->name, ['willReturnMap', 'will']);
        });

        return $nodesWithWillReturnMap !== [];
    }

    /**
     * @param string[] $methodNames
     */
    private function removeMethodCalls(Expression $expression, array $methodNames): void
    {
        $this->traverseNodesWithCallable($expression, function (Node $node) use ($methodNames): ?Node {
            if (! $node instanceof MethodCall) {
                return null;
            }

            if (! ($this->isNames($node->name, $methodNames))) {
                return null;
            }

            return $node->var;
        });
    }

    /**
     * @param Stmt[] $returnStmts
     * @return Stmt[]
     */
    private function refactorToWillReturnCallback(
        MethodCall $withConsecutiveMethodCall,
        array $returnStmts,
        Expr|Variable|null $referenceVariable,
        StaticCall|MethodCall $expectsCall,
        Expression $expression
    ): array {
        $withConsecutiveMethodCall->name = new Identifier('willReturnCallback');
        $withConsecutiveMethodCall->args = [
            new Arg($this->withConsecutiveMatchFactory->createClosure(
                $withConsecutiveMethodCall,
                $returnStmts,
                $referenceVariable
            )),
        ];

        $hasExpects = $this->findMethodCall($expression, 'expects') instanceof MethodCall;
        if ($hasExpects === false) {
            /** @var MethodCall $mockMethodCall */
            $mockMethodCall = $expression->expr;

            $mockMethodCall->var = new MethodCall($mockMethodCall->var, 'expects', [
                new Arg(new Variable('matcher')),
            ]);
        }

        $matcherAssign = new Assign(new Variable('matcher'), $expectsCall);
        return [new Expression($matcherAssign), $expression];
    }
}
