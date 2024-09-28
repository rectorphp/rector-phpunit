<?php

declare(strict_types=1);

namespace Rector\PHPUnit\NodeFactory;

use PhpParser\BuilderFactory;
use PhpParser\Node;
use PhpParser\Node\Arg;
use PhpParser\Node\Expr;
use PhpParser\Node\Expr\ArrayDimFetch;
use PhpParser\Node\Expr\BinaryOp\Minus;
use PhpParser\Node\Expr\Closure;
use PhpParser\Node\Expr\ClosureUse;
use PhpParser\Node\Expr\Match_;
use PhpParser\Node\Expr\MethodCall;
use PhpParser\Node\Expr\Variable;
use PhpParser\Node\Identifier;
use PhpParser\Node\MatchArm;
use PhpParser\Node\Param;
use PhpParser\Node\Scalar\LNumber;
use PhpParser\Node\Stmt;
use PhpParser\Node\Stmt\Expression;
use Rector\NodeNameResolver\NodeNameResolver;
use Rector\PhpParser\Node\BetterNodeFinder;

final readonly class WithConsecutiveMatchFactory
{
    public function __construct(
        private NodeNameResolver $nodeNameResolver,
        private BetterNodeFinder $betterNodeFinder,
        private BuilderFactory $builderFactory,
        private MatcherNodeFactory $matcherNodeFactory,
    ) {
    }

    /**
     * @param Stmt[] $returnStmts
     */
    public function createClosure(
        MethodCall $withConsecutiveMethodCall,
        array $returnStmts,
        Variable|Expr|null $referenceVariable,
        bool $isWithConsecutiveVariadic
    ): Closure {
        $matcherVariable = new Variable('matcher');
        $usedVariables = $this->resolveUsedVariables($withConsecutiveMethodCall, $returnStmts);

        $isByRef = $this->isByRef($referenceVariable);
        $uses = $this->createUses($matcherVariable, $usedVariables);

        $parametersVariable = new Variable('parameters');
        $match = $this->createParametersMatch($withConsecutiveMethodCall, $parametersVariable);

        $parametersParam = new Param($parametersVariable);
        if ($isWithConsecutiveVariadic) {
            $parametersParam->variadic = true;
        }

        return new Closure([
            'byRef' => $isByRef,
            'uses' => $uses,
            'params' => [$parametersParam],
            'stmts' => [new Expression($match), ...$returnStmts],
        ]);
    }

    public function createParametersMatch(
        MethodCall $withConsecutiveMethodCall,
        Variable $parametersVariable
    ): Match_|MethodCall {
        $firstArg = $withConsecutiveMethodCall->getArgs()[0] ?? null;
        if ($firstArg instanceof Arg && $firstArg->unpack) {
            return $this->createAssertSameDimFetch($firstArg, new Variable('matcher'), $parametersVariable);
        }

        $numberOfInvocationsMethodCall = $this->matcherNodeFactory->create();

        $matchArms = [];
        foreach ($withConsecutiveMethodCall->getArgs() as $key => $arg) {
            $assertEquals = $this->builderFactory->staticCall('self', 'assertEquals', [$arg, $parametersVariable]);
            $matchArms[] = new MatchArm([new LNumber($key + 1)], $assertEquals);
        }

        return new Match_($numberOfInvocationsMethodCall, $matchArms);
    }

    /**
     * @param Node[] $nodes
     * @return Variable[]
     */
    private function resolveUniqueUsedVariables(array $nodes): array
    {
        /** @var Variable[] $usedVariables */
        $usedVariables = $this->betterNodeFinder->findInstancesOfScoped($nodes, Variable::class);

        $uniqueUsedVariables = [];

        foreach ($usedVariables as $usedVariable) {
            if ($this->nodeNameResolver->isNames($usedVariable, ['this', 'matcher', 'parameters'])) {
                continue;
            }

            $usedVariableName = $this->nodeNameResolver->getName($usedVariable);
            $uniqueUsedVariables[$usedVariableName] = $usedVariable;
        }

        return $uniqueUsedVariables;
    }

    private function createAssertSameDimFetch(
        Arg $firstArg,
        Variable $matcherVariable,
        Variable $parameters
    ): MethodCall {
        $currentValueArrayDimFetch = new ArrayDimFetch($firstArg->value, new Minus(
            new MethodCall($matcherVariable, new Identifier('numberOfInvocations')),
            new LNumber(1)
        ));

        $compareArgs = [new Arg($currentValueArrayDimFetch), new Arg(new ArrayDimFetch($parameters, new LNumber(0)))];

        return $this->builderFactory->methodCall(new Variable('this'), 'assertSame', $compareArgs);
    }

    /**
     * @param Stmt[] $returnStmts
     * @return Variable[]
     */
    private function resolveUsedVariables(MethodCall $withConsecutiveMethodCall, array $returnStmts): array
    {
        $consecutiveArgs = $withConsecutiveMethodCall->getArgs();
        $stmtVariables = $this->resolveUniqueUsedVariables($returnStmts);

        return $this->resolveUniqueUsedVariables(array_merge($consecutiveArgs, $stmtVariables));
    }

    private function isByRef(Expr|Variable|null $referenceVariable): bool
    {
        return $referenceVariable instanceof Variable;
    }

    /**
     * @param Variable[] $usedVariables
     * @return ClosureUse[]
     */
    private function createUses(Variable $matcherVariable, array $usedVariables): array
    {
        $uses = [new ClosureUse($matcherVariable)];

        foreach ($usedVariables as $usedVariable) {
            $uses[] = new ClosureUse($usedVariable);
        }

        return $uses;
    }
}
