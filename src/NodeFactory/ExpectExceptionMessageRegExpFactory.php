<?php

declare(strict_types=1);

namespace Rector\PHPUnit\NodeFactory;

use PhpParser\Node\Expr\MethodCall;
use PhpParser\Node\Expr\Variable;
use PhpParser\Node\Scalar\String_;
use Rector\Core\PhpParser\Comparing\NodeComparator;
use Rector\NodeNameResolver\NodeNameResolver;
use Rector\PHPUnit\NodeAnalyzer\TestsNodeAnalyzer;

final class ExpectExceptionMessageRegExpFactory
{
    public function __construct(
        private readonly NodeNameResolver $nodeNameResolver,
        private readonly ArgumentShiftingFactory $argumentShiftingFactory,
        private readonly NodeComparator $nodeComparator,
        private readonly TestsNodeAnalyzer $testsNodeAnalyzer
    ) {
    }

    public function create(MethodCall $methodCall, Variable $exceptionVariable): ?MethodCall
    {
        if (! $this->testsNodeAnalyzer->isInPHPUnitMethodCallName($methodCall, 'assertContains')) {
            return null;
        }

        if ($methodCall->isFirstClassCallable()) {
            return;
        }

        $secondArgument = $methodCall->getArgs()[1]
->value;
        if (! $secondArgument instanceof MethodCall) {
            return null;
        }

        // looking for "$exception->getMessage()"
        if (! $this->nodeComparator->areNodesEqual($secondArgument->var, $exceptionVariable)) {
            return null;
        }

        if (! $this->nodeNameResolver->isName($secondArgument->name, 'getMessage')) {
            return null;
        }

        $this->argumentShiftingFactory->removeAllButFirstArgMethodCall(
            $methodCall,
            'expectExceptionMessageRegExp'
        );

        // put regex between "#...#" to create match
        $firstArg = $methodCall->getArgs()[0];

        if ($firstArg->value instanceof String_) {
            $oldString = $firstArg->value;
            $firstArg->value = new String_('#' . preg_quote($oldString->value, '#') . '#');
        }

        return $methodCall;
    }
}
