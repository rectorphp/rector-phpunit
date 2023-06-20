<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Rector\Class_;

use PhpParser\Node;
use PhpParser\Node\Expr\Closure;
use PhpParser\Node\Expr\MethodCall;
use PhpParser\Node\Expr\StaticCall;
use PhpParser\Node\Stmt\Class_;
use PhpParser\Node\Stmt\ClassMethod;
use PHPStan\Type\ObjectType;
use Rector\Core\Rector\AbstractRector;
use Rector\PHPUnit\NodeAnalyzer\TestsNodeAnalyzer;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;

/**
 * @see \Rector\PHPUnit\Tests\Rector\Class_\PreferPHPUnitThisCallRector\PreferPHPUnitThisCallRectorTest
 */
final class PreferPHPUnitThisCallRector extends AbstractRector
{
    public function __construct(
        private readonly TestsNodeAnalyzer $testsNodeAnalyzer,
    ) {
    }

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition('Changes PHPUnit calls from self::assert*() to $this->assert*()', [
            new CodeSample(
                <<<'CODE_SAMPLE'
use PHPUnit\Framework\TestCase;

final class SomeClass extends TestCase
{
    public function run()
    {
        self::assertEquals('expected', $result);
    }
}
CODE_SAMPLE
                ,
                <<<'CODE_SAMPLE'
use PHPUnit\Framework\TestCase;

final class SomeClass extends TestCase
{
    public function run()
    {
        $this->assertEquals('expected', $result);
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

        $hasChanged = false;
        $isStatic = false;
        $this->traverseNodesWithCallable($node, function (Node $node) use (&$hasChanged, &$isStatic): ?MethodCall {
            $isStatic = ($isStatic) || ($node instanceof ClassMethod && $node->isStatic()) || ($node instanceof Closure && $node->static);
            if (! $node instanceof StaticCall || $isStatic) {
                return null;
            }

            $methodName = $this->getName($node->name);
            if (! is_string($methodName)) {
                return null;
            }

            if (! $this->isNames($node->class, ['static', 'self'])) {
                return null;
            }

            if (! $this->isObjectType($node->class, new ObjectType('PHPUnit\Framework\TestCase'))) {
                return null;
            }

            if (! $this->isName($node->name, 'assert*')) {
                return null;
            }

            $hasChanged = true;
            return $this->nodeFactory->createMethodCall('this', $methodName, $node->getArgs());
        });

        if ($hasChanged) {
            return $node;
        }

        return null;
    }
}
