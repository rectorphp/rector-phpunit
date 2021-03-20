<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Rector\Foreach_;

use PhpParser\Node;
use PhpParser\Node\Arg;
use PhpParser\Node\Expr\MethodCall;
use PhpParser\Node\Expr\StaticCall;
use PhpParser\Node\Name;
use PhpParser\Node\Stmt\Foreach_;
use Rector\Core\NodeManipulator\ForeachManipulator;
use Rector\Core\Rector\AbstractRector;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;

/**
 * @see \Rector\PHPUnit\Tests\Rector\Foreach_\SimplifyForeachInstanceOfRector\SimplifyForeachInstanceOfRectorTest
 */
final class SimplifyForeachInstanceOfRector extends AbstractRector
{
    /**
     * @var ForeachManipulator
     */
    private $foreachManipulator;

    public function __construct(ForeachManipulator $foreachManipulator)
    {
        $this->foreachManipulator = $foreachManipulator;
    }

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition(
            'Simplify unnecessary foreach check of instances',
            [
                new CodeSample(
                    <<<'CODE_SAMPLE'
foreach ($foos as $foo) {
    $this->assertInstanceOf(SplFileInfo::class, $foo);
}
CODE_SAMPLE
                    ,
                    '$this->assertContainsOnlyInstancesOf(\SplFileInfo::class, $foos);'
            ),
            ]);
    }

    /**
     * @return array<class-string<Node>>
     */
    public function getNodeTypes(): array
    {
        return [Foreach_::class];
    }

    /**
     * @param Foreach_ $node
     */
    public function refactor(Node $node): ?Node
    {
        /** @var MethodCall|StaticCall|null $matchedNode */
        $matchedNode = $this->foreachManipulator->matchOnlyStmt(
            $node,
            function (Node $node, Foreach_ $foreachNode): ?Node {
                if (! $node instanceof MethodCall && ! $node instanceof StaticCall) {
                    return null;
                }

                if (! $this->isName($node->name, 'assertInstanceOf')) {
                    return null;
                }

                if (! $this->nodeComparator->areNodesEqual($foreachNode->valueVar, $node->args[1]->value)) {
                    return null;
                }

                return $node;
            }
        );

        if ($matchedNode === null) {
            return null;
        }

        /** @var MethodCall|StaticCall $matchedNode */
        $callClass = get_class($matchedNode);

        return new $callClass(
            $this->resolveVar($matchedNode),
            new Name('assertContainsOnlyInstancesOf'),
            [$matchedNode->args[0], new Arg($node->expr)]
        );
    }

    /**
     * @param MethodCall|StaticCall $node
     */
    private function resolveVar(Node $node): Node
    {
        if ($node instanceof MethodCall) {
            return $node->var;
        }

        return $node->class;
    }
}
