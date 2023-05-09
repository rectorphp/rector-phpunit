<?php

declare(strict_types=1);

namespace Rector\PHPUnit\NodeFactory;

use PhpParser\Node\Expr\MethodCall;
use PhpParser\Node\Expr\Variable;
use Rector\NodeNameResolver\NodeNameResolver;
use Rector\PHPUnit\NodeAnalyzer\TestsNodeAnalyzer;

final class ExpectExceptionCodeFactory
{
    public function __construct(
        private readonly NodeNameResolver $nodeNameResolver,
        private readonly ArgumentShiftingFactory $argumentShiftingFactory,
        private readonly TestsNodeAnalyzer $testsNodeAnalyzer
    ) {
    }

    public function create(MethodCall $methodCall, Variable $exceptionVariable): ?MethodCall
    {
        if (! $this->testsNodeAnalyzer->isPHPUnitMethodCallNames($methodCall, ['assertSame', 'assertEquals'])) {
            return null;
        }

        $secondArgument = $methodCall->getArgs()[1]
->value;
        if (! $secondArgument instanceof MethodCall) {
            return null;
        }

        // looking for "$exception->getMessage()"
        if (! $this->nodeNameResolver->areNamesEqual($secondArgument->var, $exceptionVariable)) {
            return null;
        }

        if (! $this->nodeNameResolver->isName($secondArgument->name, 'getCode')) {
            return null;
        }

        $this->argumentShiftingFactory->removeAllButFirstArgMethodCall($methodCall, 'expectExceptionCode');
        return $methodCall;
    }
}
