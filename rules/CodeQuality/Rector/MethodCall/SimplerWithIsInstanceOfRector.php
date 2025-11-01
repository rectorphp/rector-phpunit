<?php

declare(strict_types=1);

namespace Rector\PHPUnit\CodeQuality\Rector\MethodCall;

use PhpParser\Node;
use PhpParser\Node\Expr\Closure;
use PhpParser\Node\Expr\Instanceof_;
use PhpParser\Node\Expr\MethodCall;
use Rector\PHPUnit\NodeAnalyzer\TestsNodeAnalyzer;
use Rector\Rector\AbstractRector;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;

/**
 * @see \Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\SimplerWithIsInstanceOfRector\SimplerWithIsInstanceOfRectorTest
 */
final class SimplerWithIsInstanceOfRector extends AbstractRector
{
    public function __construct(
        private readonly TestsNodeAnalyzer $testsNodeAnalyzer
    ) {
    }

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition(
            'Replaces use of with, callable and instance assert to simple isInstanceOf() method',
            [
                new CodeSample(
                    <<<'CODE_SAMPLE'
use PHPUnit\Framework\TestCase

final class SomeClass extends TestCase
{
    public function test()
    {
        $someMock = $this->createMock(SomeClass::class)
            ->method('someMethod')
            ->with($this->callable(function ($arg): bool {
                return $arg instanceof SomeType;
            }));
    }
}
CODE_SAMPLE
                    ,
                    <<<'CODE_SAMPLE'
use PHPUnit\Framework\TestCase;

final class SomeClass extends TestCase
{
    public function test()
    {
        $someMock = $this->createMock(SomeClass::class)
            ->method('someMethod')
            ->with($this->isInstanceOf(SomeType::class));
    }
}
CODE_SAMPLE
                ),
            ]
        );
    }

    public function getNodeTypes(): array
    {
        return [MethodCall::class];
    }

    /**
     * @param MethodCall $node
     */
    public function refactor(Node $node): MethodCall|null
    {
        if (! $this->testsNodeAnalyzer->isInTestClass($node)) {
            return null;
        }

        if ($node->isFirstClassCallable()) {
            return null;
        }

        if (! $this->isName($node->name, 'with')) {
            return null;
        }

        $withFirstArgValue = $node->getArgs()[0]
            ->value;
        if (! $withFirstArgValue instanceof MethodCall || ! $this->isName($withFirstArgValue->name, 'callback')) {
            return null;
        }

        $callableMethodCall = $withFirstArgValue;
        $callableFirstArgValue = $callableMethodCall->getArgs()[0]
            ->value;

        $innerClosure = $callableFirstArgValue;
        if (! $innerClosure instanceof Closure) {
            return null;
        }

        $instanceCheckedClassName = $this->matchSoleInstanceofCheckClassName($innerClosure);

        if (! $instanceCheckedClassName instanceof \PhpParser\Node) {
            return null;
        }

        // convert name to expr
        if ($instanceCheckedClassName instanceof Node\Name) {
            $instanceCheckedClassName = $this->nodeFactory->createClassConstFetch(
                $instanceCheckedClassName->toString(),
                'class'
            );
        }

        $node->args = [
            new Node\Arg($this->nodeFactory->createMethodCall('this', 'isInstanceOf', [$instanceCheckedClassName])),
        ];

        return $node;
    }

    private function matchSoleInstanceofCheckClassName(Closure $innerClosure): Node|null|Node\Expr|Node\Name
    {
        // return + instancecheck only
        $innerClosureStmts = $innerClosure->getStmts();

        if (count($innerClosureStmts) === 2) {
            if (! $innerClosureStmts[1] instanceof Node\Stmt\Return_) {
                return null;
            }

            $firstStmt = $innerClosureStmts[0];

            if (! $firstStmt instanceof Node\Stmt\Expression) {
                return null;
            }

            $firstStmtExpr = $firstStmt->expr;
            if (! $firstStmtExpr instanceof MethodCall) {
                return null;
            }

            if (! $this->isName($firstStmtExpr->name, 'assertInstanceOf')) {
                return null;
            }

            return $firstStmtExpr->getArgs()[0]
                ->value;
        } elseif (count($innerClosureStmts) === 1) {
            $onlyStmt = $innerClosureStmts[0];
            if (! $onlyStmt instanceof Node\Stmt\Return_) {
                return null;
            }

            $returnExpr = $onlyStmt->expr;
            if (! $returnExpr instanceof Instanceof_) {
                return null;
            }

            $instanceofExpr = $returnExpr;
            if (! $instanceofExpr->class instanceof Node\Name) {
                return null;
            }

            return $instanceofExpr->class;
        }
        return null;

    }
}
