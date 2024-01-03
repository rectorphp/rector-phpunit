<?php

declare(strict_types=1);

namespace Rector\PHPUnit\NodeAnalyzer;

use PhpParser\Node;
use PhpParser\Node\Expr\PropertyFetch;
use PhpParser\Node\Expr\StaticCall;
use PhpParser\Node\Expr\Variable;
use PhpParser\Node\Stmt\ClassMethod;
use PHPStan\Type\IntersectionType;
use PHPStan\Type\MixedType;
use PHPStan\Type\ObjectType;
use PHPStan\Type\Type;
use Rector\NodeNameResolver\NodeNameResolver;
use Rector\NodeTypeResolver\NodeTypeResolver;
use Rector\PhpDocParser\NodeTraverser\SimpleCallableNodeTraverser;

final readonly class MockedVariableAnalyzer
{
    public function __construct(
        private SimpleCallableNodeTraverser $simpleCallableNodeTraverser,
        private NodeNameResolver $nodeNameResolver,
        private NodeTypeResolver $nodeTypeResolver
    ) {
    }

    public function containsMockAsUsedVariable(ClassMethod $classMethod): bool
    {
        $doesContainMock = false;

        $this->simpleCallableNodeTraverser->traverseNodesWithCallable($classMethod, function (Node $node) use (
            &$doesContainMock
        ): null {
            if ($this->isMockeryStaticCall($node)) {
                $doesContainMock = true;
                return null;
            }

            if (! $node instanceof PropertyFetch && ! $node instanceof Variable) {
                return null;
            }

            $variableType = $this->nodeTypeResolver->getType($node);
            if ($variableType instanceof MixedType) {
                return null;
            }

            if ($this->isIntersectionTypeWithMockObject($variableType)) {
                $doesContainMock = true;
            }

            if ($variableType->isSuperTypeOf(new ObjectType('PHPUnit\Framework\MockObject\MockObject'))->yes()) {
                $doesContainMock = true;
            }

            return null;
        });

        return $doesContainMock;
    }

    private function isIntersectionTypeWithMockObject(Type $variableType): bool
    {
        if ($variableType instanceof IntersectionType) {
            foreach ($variableType->getTypes() as $variableTypeType) {
                if ($variableTypeType->isSuperTypeOf(
                    new ObjectType('PHPUnit\Framework\MockObject\MockObject')
                )->yes()) {
                    return true;
                }
            }
        }

        return false;
    }

    private function isMockeryStaticCall(Node $node): bool
    {
        if (! $node instanceof StaticCall) {
            return false;
        }

        // is mockery mock
        if (! $this->nodeNameResolver->isName($node->class, 'Mockery')) {
            return false;
        }

        return $this->nodeNameResolver->isName($node->name, 'mock');
    }
}
