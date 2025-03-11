<?php

declare(strict_types=1);

namespace Rector\PHPUnit\CodeQuality\NodeAnalyser;

use PhpParser\Node\Expr\Assign;
use PhpParser\Node\Expr\MethodCall;
use PhpParser\Node\Expr\Variable;
use PHPStan\Type\ObjectType;
use PHPStan\Type\TypeCombinator;
use Rector\NodeNameResolver\NodeNameResolver;
use Rector\NodeTypeResolver\NodeTypeResolver;
use Rector\PHPUnit\CodeQuality\ValueObject\VariableNameToType;

final class NullableObjectAssignCollector
{
    public function __construct(
        private readonly NodeNameResolver $nodeNameResolver,
        private readonly NodeTypeResolver $nodeTypeResolver,
    ) {
    }

    public function collect(Assign $assign): ?VariableNameToType
    {
        if (! $assign->expr instanceof MethodCall) {
            return null;
        }

        if (! $assign->var instanceof Variable) {
            return null;
        }

        $variableName = $this->nodeNameResolver->getName($assign->var);
        $variableType = $this->nodeTypeResolver->getType($assign);

        $bareVariableType = TypeCombinator::removeNull($variableType);
        if (! $bareVariableType instanceof ObjectType) {
            return null;
        }

        return new VariableNameToType($variableName, $bareVariableType->getClassName());
    }
}
