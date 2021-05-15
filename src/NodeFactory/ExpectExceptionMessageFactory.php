<?php

declare(strict_types=1);

namespace Rector\PHPUnit\NodeFactory;

use PhpParser\Node\Expr\MethodCall;
use PhpParser\Node\Expr\Variable;
use Rector\Core\PhpParser\Comparing\NodeComparator;
use Rector\NodeNameResolver\NodeNameResolver;
use Rector\NodeTypeResolver\NodeTypeResolver;
use Rector\PHPUnit\NodeAnalyzer\TestsNodeAnalyzer;

final class ExpectExceptionMessageFactory
{
    public function __construct(
        private NodeNameResolver $nodeNameResolver,
        private ArgumentShiftingFactory $argumentShiftingFactory,
        private NodeComparator $nodeComparator,
        private NodeTypeResolver $nodeTypeResolver,
        private TestsNodeAnalyzer $testsNodeAnalyzer
    ) {
    }

    public function create(MethodCall $methodCall, Variable $exceptionVariable): ?MethodCall
    {
        if (! $this->testsNodeAnalyzer->isPHPUnitMethodCallNames($methodCall, ['assertSame', 'assertEquals'])) {
            return null;
        }

        $secondArgument = $methodCall->args[1]->value;
        if (! $secondArgument instanceof MethodCall) {
            return null;
        }

        if (! $this->nodeComparator->areNodesEqual($secondArgument->var, $exceptionVariable)) {
            return null;
        }

        if (! $this->nodeNameResolver->isName($secondArgument->name, 'getMessage')) {
            return null;
        }

        $this->argumentShiftingFactory->removeAllButFirstArgMethodCall($methodCall, 'expectExceptionMessage');
        return $methodCall;
    }
}
