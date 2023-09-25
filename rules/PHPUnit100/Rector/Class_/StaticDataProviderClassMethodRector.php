<?php

declare(strict_types=1);

namespace Rector\PHPUnit\PHPUnit100\Rector\Class_;

use PhpParser\Node;
use PhpParser\Node\Expr\Closure;
use PhpParser\Node\Expr\MethodCall;
use PhpParser\Node\Expr\StaticCall;
use PhpParser\Node\Expr\Variable;
use PhpParser\Node\Identifier;
use PhpParser\Node\Stmt\Class_;
use PhpParser\Node\Stmt\ClassMethod;
use PhpParser\Node\Stmt\Function_;
use PhpParser\NodeTraverser;
use Rector\Core\Rector\AbstractRector;
use Rector\PHPUnit\NodeAnalyzer\TestsNodeAnalyzer;
use Rector\PHPUnit\NodeFinder\DataProviderClassMethodFinder;
use Rector\Privatization\NodeManipulator\VisibilityManipulator;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;

/**
 * @see \Rector\PHPUnit\Tests\PHPUnit100\Rector\Class_\StaticDataProviderClassMethodRector\StaticDataProviderClassMethodRectorTest
 */
final class StaticDataProviderClassMethodRector extends AbstractRector
{
    public function __construct(
        private readonly TestsNodeAnalyzer $testsNodeAnalyzer,
        private readonly DataProviderClassMethodFinder $dataProviderClassMethodFinder,
        private readonly VisibilityManipulator $visibilityManipulator,
    ) {
    }

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition('Change data provider methods to static', [
            new CodeSample(
                <<<'CODE_SAMPLE'
use PHPUnit\Framework\TestCase;

final class SomeTest extends TestCase
{
    /**
     * @dataProvider provideData()
     */
    public function test()
    {
    }

    public function provideData()
    {
        yield [1];
    }
}
CODE_SAMPLE

                ,
                <<<'CODE_SAMPLE'
use PHPUnit\Framework\TestCase;

final class SomeTest extends TestCase
{
    /**
     * @dataProvider provideData()
     */
    public function test()
    {
    }

    public static function provideData()
    {
        yield [1];
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
        return [Class_::class];
    }

    /**
     * @param Class_ $node
     */
    public function refactor(Node $node): ?Node
    {
        if (! $this->testsNodeAnalyzer->isInTestClass($node)) {
            return null;
        }

        // 1. find all data providers
        $dataProviderClassMethods = $this->dataProviderClassMethodFinder->find($node);

        $hasChanged = false;

        foreach ($dataProviderClassMethods as $dataProviderClassMethod) {
            if ($this->skipMethod($dataProviderClassMethod)) {
                continue;
            }

            $this->visibilityManipulator->makeStatic($dataProviderClassMethod);

            $this->traverseNodesWithCallable(
                (array) $dataProviderClassMethod->stmts,
                function (Node $subNode): int|null|StaticCall {
                    if ($subNode instanceof Class_ || $subNode instanceof Function_ || $subNode instanceof Closure) {
                        return NodeTraverser::DONT_TRAVERSE_CURRENT_AND_CHILDREN;
                    }

                    if (! $subNode instanceof MethodCall) {
                        return null;
                    }

                    if ($subNode->isFirstClassCallable()) {
                        return null;
                    }

                    if (! $this->isName($subNode->var, 'this')) {
                        return null;
                    }

                    if (! $subNode->name instanceof Identifier) {
                        return null;
                    }

                    return $this->nodeFactory->createStaticCall('self', $subNode->name->toString(), $subNode->getArgs());
                }
            );

            $hasChanged = true;
        }

        if ($hasChanged) {
            return $node;
        }

        return null;
    }

    private function skipMethod(ClassMethod $classMethod): bool
    {
        if ($classMethod->isStatic()) {
            return true;
        }

        if ($classMethod->stmts === null) {
            return false;
        }

        return (bool) $this->betterNodeFinder->findFirst(
            $classMethod->stmts,
            fn (Node $node): bool => $node instanceof Variable && $this->nodeNameResolver->isName($node, 'this')
        );
    }
}
