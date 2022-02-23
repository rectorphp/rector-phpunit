<?php

declare(strict_types=1);

namespace Rector\PHPUnit\NodeAnalyzer;

use PhpParser\Node;
use PhpParser\Node\Expr\PropertyFetch;
use PhpParser\Node\Expr\Variable;
use PhpParser\Node\Stmt\ClassMethod;
use PHPStan\Type\MixedType;
use PHPStan\Type\ObjectType;
use Rector\NodeTypeResolver\NodeTypeResolver;
use Symplify\Astral\NodeTraverser\SimpleCallableNodeTraverser;

final class MockedVariableAnalyzer
{
    public function __construct(
        private SimpleCallableNodeTraverser $simpleCallableNodeTraverser,
        private NodeTypeResolver $nodeTypeResolver
    ) {
    }

    public function containsMockAsUsedVariable(ClassMethod $classMethod): bool
    {
        $doesContainMock = false;

        $this->simpleCallableNodeTraverser->traverseNodesWithCallable($classMethod, function (Node $node) use (
            &$doesContainMock
        ) {
            if (! $node instanceof PropertyFetch && ! $node instanceof Variable) {
                return null;
            }

            $variableType = $this->nodeTypeResolver->getType($node);
            if ($variableType instanceof MixedType) {
                return null;
            }

            if ($variableType->isSuperTypeOf(new ObjectType('PHPUnit\Framework\MockObject\MockObject'))->yes()) {
                $doesContainMock = true;
            }

            return null;
        });

        return $doesContainMock;
    }
}
