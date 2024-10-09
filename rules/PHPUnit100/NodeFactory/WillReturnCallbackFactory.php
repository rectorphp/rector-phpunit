<?php

declare(strict_types=1);

namespace Rector\PHPUnit\PHPUnit100\NodeFactory;

use PhpParser\BuilderFactory;
use PhpParser\Node\Arg;
use PhpParser\Node\Expr;
use PhpParser\Node\Expr\ArrayDimFetch;
use PhpParser\Node\Expr\BinaryOp\Minus;
use PhpParser\Node\Expr\Closure;
use PhpParser\Node\Expr\ClosureUse;
use PhpParser\Node\Expr\MethodCall;
use PhpParser\Node\Expr\Variable;
use PhpParser\Node\Param;
use PhpParser\Node\Scalar\LNumber;
use PhpParser\Node\Stmt;
use PhpParser\Node\Stmt\Expression;
use Rector\PHPUnit\Enum\ConsecutiveVariable;
use Rector\PHPUnit\NodeFactory\ConsecutiveIfsFactory;
use Rector\PHPUnit\NodeFactory\MatcherInvocationCountMethodCallNodeFactory;
use Rector\PHPUnit\NodeFactory\UsedVariablesResolver;

final readonly class WillReturnCallbackFactory
{
    public function __construct(
        private BuilderFactory $builderFactory,
        private UsedVariablesResolver $usedVariablesResolver,
        private MatcherInvocationCountMethodCallNodeFactory $matcherInvocationCountMethodCallNodeFactory,
        private ConsecutiveIfsFactory $consecutiveIfsFactory,
    ) {
    }

    public function createClosure(
        MethodCall $withConsecutiveMethodCall,
        ?Stmt $returnStmt,
        Variable|Expr|null $referenceVariable,
    ): Closure {
        $matcherVariable = new Variable(ConsecutiveVariable::MATCHER);
        $usedVariables = $this->usedVariablesResolver->resolveUsedVariables($withConsecutiveMethodCall, $returnStmt);

        $closureStmts = $this->createParametersMatch($withConsecutiveMethodCall);
        if ($returnStmt instanceof Stmt) {
            $closureStmts[] = $returnStmt;
        }

        $parametersParam = new Param(new Variable(ConsecutiveVariable::PARAMETERS));
        $parametersParam->variadic = true;

        return new Closure([
            'byRef' => $this->isByRef($referenceVariable),
            'uses' => $this->createClosureUses($matcherVariable, $usedVariables),
            'params' => [$parametersParam],
            'stmts' => $closureStmts,
        ]);
    }

    /**
     * @return Stmt[]
     */
    public function createParametersMatch(MethodCall $withConsecutiveMethodCall): array
    {
        $parametersVariable = new Variable(ConsecutiveVariable::PARAMETERS);

        $firstArg = $withConsecutiveMethodCall->getArgs()[0] ?? null;
        if ($firstArg instanceof Arg && $firstArg->unpack) {
            $assertSameMethodCall = $this->createAssertSameDimFetch($firstArg, $parametersVariable);
            return [new Expression($assertSameMethodCall)];
        }

        $numberOfInvocationsMethodCall = $this->matcherInvocationCountMethodCallNodeFactory->create();

        return $this->consecutiveIfsFactory->createIfs($withConsecutiveMethodCall, $numberOfInvocationsMethodCall);
    }

    private function createAssertSameDimFetch(Arg $firstArg, Variable $variable): MethodCall
    {
        $matcherCountMethodCall = $this->matcherInvocationCountMethodCallNodeFactory->create();

        $currentValueArrayDimFetch = new ArrayDimFetch($firstArg->value, new Minus(
            $matcherCountMethodCall,
            new LNumber(1)
        ));

        $compareArgs = [new Arg($currentValueArrayDimFetch), new Arg($variable)];

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
