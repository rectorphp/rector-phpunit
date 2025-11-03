<?php

declare(strict_types=1);

namespace Rector\PHPUnit\CodeQuality\NodeAnalyser;

use PhpParser\Node\ClosureUse;
use PhpParser\Node\Expr\ArrowFunction;
use PhpParser\Node\Expr\Variable;
use Rector\NodeNameResolver\NodeNameResolver;
use Rector\PhpParser\Node\BetterNodeFinder;

final readonly class ClosureUsesResolver
{
    public function __construct(
        private BetterNodeFinder $betterNodeFinder,
        private NodeNameResolver $nodeNameResolver
    ) {

    }

    /**
     * @return ClosureUse[]
     */
    public function resolveFromArrowFunction(ArrowFunction $arrowFunction): array
    {
        // fill needed uses from arrow function to closure
        $arrowFunctionVariables = $this->betterNodeFinder->findInstancesOfScoped(
            $arrowFunction->getStmts(),
            Variable::class
        );

        $paramNames = $this->resolveParamNames($arrowFunction);

        $externalVariableNames = [];

        foreach ($arrowFunctionVariables as $arrowFunctionVariable) {
            // skip those defined in params
            if ($this->nodeNameResolver->isNames($arrowFunctionVariable, $paramNames)) {
                continue;
            }

            $variableName = $this->nodeNameResolver->getName($arrowFunctionVariable);
            if (! is_string($variableName)) {
                continue;
            }

            $externalVariableNames[] = $variableName;
        }

        $externalVariableNames = array_unique($externalVariableNames);
        $externalVariableNames = array_diff($externalVariableNames, ['this']);

        $closureUses = [];
        foreach ($externalVariableNames as $externalVariableName) {
            $closureUses[] = new ClosureUse(new Variable($externalVariableName));
        }

        return $closureUses;
    }

    /**
     * @return string[]
     */
    private function resolveParamNames(ArrowFunction $arrowFunction): array
    {
        $paramNames = [];
        foreach ($arrowFunction->getParams() as $param) {
            $paramNames[] = $this->nodeNameResolver->getName($param);
        }

        return $paramNames;
    }
}
