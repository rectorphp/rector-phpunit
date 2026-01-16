<?php

declare(strict_types=1);

namespace Rector\PHPUnit\CodeQuality\ValueObject;

use PhpParser\Node\Arg;
use PhpParser\Node\Expr\ArrowFunction;
use PhpParser\Node\Expr\Closure;

final readonly class ArgAndFunctionLike
{
    public function __construct(
        private Arg $arg,
        private Closure|ArrowFunction $functionLike
    ) {
    }

    public function getArg(): Arg
    {
        return $this->arg;
    }

    public function getFunctionLike(): Closure|ArrowFunction
    {
        return $this->functionLike;
    }
}
