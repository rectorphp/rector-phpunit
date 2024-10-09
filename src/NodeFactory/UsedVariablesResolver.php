<?php

declare(strict_types=1);

namespace Rector\PHPUnit\NodeFactory;

use PhpParser\Node;
use PhpParser\Node\Expr\MethodCall;
use PhpParser\Node\Expr\Variable;
use PhpParser\Node\Stmt;
use Rector\NodeNameResolver\NodeNameResolver;
use Rector\PhpParser\Node\BetterNodeFinder;
use Rector\PHPUnit\Enum\ConsecutiveVariable;

final readonly class UsedVariablesResolver
{
    public function __construct(
        private BetterNodeFinder $betterNodeFinder,
        private NodeNameResolver $nodeNameResolver
    ) {
    }

    /**
     * @return Variable[]
     */
    public function resolveUsedVariables(MethodCall $withConsecutiveMethodCall, ?Stmt $returnStmt): array
    {
        $consecutiveArgs = $withConsecutiveMethodCall->getArgs();

        $stmtVariables = $returnStmt instanceof Stmt ? $this->resolveUniqueVariables([$returnStmt]) : [];

        return $this->resolveUniqueVariables(array_merge($consecutiveArgs, $stmtVariables));
    }

    /**
     * @param Node[] $nodes
     * @return Variable[]
     */
    private function resolveUniqueVariables(array $nodes): array
    {
        /** @var Variable[] $usedVariables */
        $usedVariables = $this->betterNodeFinder->findInstancesOfScoped($nodes, Variable::class);

        $uniqueUsedVariables = [];

        foreach ($usedVariables as $usedVariable) {
            if ($this->nodeNameResolver->isNames(
                $usedVariable,
                ['this', ConsecutiveVariable::MATCHER, ConsecutiveVariable::PARAMETERS]
            )) {
                continue;
            }

            $usedVariableName = $this->nodeNameResolver->getName($usedVariable);
            $uniqueUsedVariables[$usedVariableName] = $usedVariable;
        }

        return $uniqueUsedVariables;
    }
}
