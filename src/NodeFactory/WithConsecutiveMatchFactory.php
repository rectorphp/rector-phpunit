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
use PhpParser\NodeFinder;
use Rector\NodeNameResolver\NodeNameResolver;
use Rector\PHPUnit\Enum\ConsecutiveVariable;

final readonly class WithConsecutiveMatchFactory
{
    public function __construct(
        private BuilderFactory $builderFactory,
        private UsedVariablesResolver $usedVariablesResolver,
        private MatcherInvocationCountMethodCallNodeFactory $matcherInvocationCountMethodCallNodeFactory,
        private NodeFinder $nodeFinder,
        private NodeNameResolver $nodeNameResolver,
        private ConsecutiveIfsFactory $consecutiveIfsFactory,
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
        $matcherVariable = new Variable(ConsecutiveVariable::MATCHER);
        $usedVariables = $this->usedVariablesResolver->resolveUsedVariables($withConsecutiveMethodCall, $returnStmts);

        $matchOrIfs = $this->createParametersMatch($withConsecutiveMethodCall);

        if (is_array($matchOrIfs)) {
            $closureStmts = array_merge($matchOrIfs, $returnStmts);
        } else {
            $closureStmts = [new Expression($matchOrIfs), ...$returnStmts];
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
     * @return Match_|MethodCall|Stmt\If_[]
     */
    public function createParametersMatch(MethodCall $withConsecutiveMethodCall): Match_|MethodCall|array
    {
        $parametersVariable = new Variable(ConsecutiveVariable::PARAMETERS);

        $firstArg = $withConsecutiveMethodCall->getArgs()[0] ?? null;
        if ($firstArg instanceof Arg && $firstArg->unpack) {
            return $this->createAssertSameDimFetch($firstArg, $parametersVariable);
        }

        $numberOfInvocationsMethodCall = $this->matcherInvocationCountMethodCallNodeFactory->create();

        // A. has assert inside the on consecutive? create ifs
        if ($this->hasInnerAssertCall($withConsecutiveMethodCall)) {
            return $this->consecutiveIfsFactory->createIfs($withConsecutiveMethodCall);
        }

        // B. if not, create match

        $matchArms = [];
        foreach ($withConsecutiveMethodCall->getArgs() as $key => $arg) {
            $assertEquals = $this->builderFactory->staticCall('self', 'assertEquals', [$arg, $parametersVariable]);
            $matchArms[] = new MatchArm([new LNumber($key + 1)], $assertEquals);
        }

        return new Match_($numberOfInvocationsMethodCall, $matchArms);
    }

    private function createAssertSameDimFetch(Arg $firstArg, Variable $variable): MethodCall
    {
        $currentValueArrayDimFetch = new ArrayDimFetch($firstArg->value, new Minus(
            new MethodCall(new Variable(ConsecutiveVariable::MATCHER), new Identifier('numberOfInvocations')),
            new LNumber(1)
        ));

        $compareArgs = [new Arg($currentValueArrayDimFetch), new Arg(new ArrayDimFetch($variable, new LNumber(0)))];

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

    /**
     * We look for $this->assert/equals*() calls inside the consecutive calls
     */
    private function hasInnerAssertCall(MethodCall $withConsecutiveMethodCall): bool
    {
        return (bool) $this->nodeFinder->findFirst($withConsecutiveMethodCall->getArgs(), function (Node $node): bool {
            if (! $node instanceof MethodCall) {
                return false;
            }

            if (! $node->var instanceof Variable) {
                return false;
            }

            if (! $this->nodeNameResolver->isName($node->var, 'this')) {
                return false;
            }

            if (! $node->name instanceof Identifier) {
                return false;
            }

            // is one of assert methods
            return str_starts_with($node->name->toString(), 'equal');
        });
    }
}
