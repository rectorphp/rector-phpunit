<?php

declare(strict_types=1);

namespace Rector\PHPUnit\NodeFactory;

use PhpParser\Node\Expr\MethodCall;
use PhpParser\Node\Expr\StaticCall;

final class AssertCallFactory
{
    public function createCallWithName(StaticCall|MethodCall $node, string $name): StaticCall|MethodCall
    {
        if ($node instanceof MethodCall) {
            return new MethodCall($node->var, $name);
        }

        return new StaticCall($node->class, $name);
    }
}
