<?php

declare(strict_types=1);

namespace Rector\PHPUnit\NodeManipulator;

use PhpParser\Node\Expr\MethodCall;
use PhpParser\Node\Expr\StaticCall;

final class ArgumentMover
{
    public function removeFirst(MethodCall|StaticCall $node): void
    {
        if ($node->isFirstClassCallable()) {
            return;
        }

        $methodArguments = $node->getArgs();
        array_shift($methodArguments);

        $node->args = $methodArguments;
    }
}
