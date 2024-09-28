<?php

declare(strict_types=1);

namespace Rector\PHPUnit\NodeFactory;

use PhpParser\BuilderFactory;
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

final readonly class WithConsecutiveMatchFactory
{
    public function __construct(
        private BuilderFactory $builderFactory,
        private UsedVariablesResolver $usedVariablesResolver,
        private MatcherNodeFactory $matcherNodeFactory,
    ) {
    }

    /**
     * @param Stmt[] $returnStmts
     */
    public function createClosure(
        MethodCall $withConsecutiveMethodCall,
        array $returnStmts,
        Variable|Expr|null $referenceVariable
    ): Closure {
        $matcherVariable = new Variable('matcher');
        $usedVariables = $this->usedVariablesResolver->resolveUsedVariables($withConsecutiveMethodCall, $returnStmts);

        $parametersVariable = new Variable('parameters');
        $match = $this->createParametersMatch($withConsecutiveMethodCall, $parametersVariable);

        $parametersParam = new Param($parametersVariable);
        $parametersParam->variadic = true;

        return new Closure([
            'byRef' => $this->isByRef($referenceVariable),
            'uses' => $this->createClosureUses($matcherVariable, $usedVariables),
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

    private function isByRef(Expr|Variable|null $referenceVariable): bool
    {
        return $referenceVariable instanceof Variable;
    }

    /**
     * @param Variable[] $usedVariables
     * @return ClosureUse[]
     */
    private function createClosureUses(Variable $matcherVariable, array $usedVariables): array
    {
        $uses = [new ClosureUse($matcherVariable)];

        foreach ($usedVariables as $usedVariable) {
            $uses[] = new ClosureUse($usedVariable);
        }

        return $uses;
    }
}
