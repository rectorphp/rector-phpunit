<?php

declare(strict_types=1);

namespace Rector\PHPUnit\CodeQuality\ValueObject;

use PhpParser\Node\Expr;
use PhpParser\Node\Expr\Variable;

final readonly class VariableAndDimFetch
{
    public function __construct(
        private Variable $variable,
        private Expr $dimFetchExpr
    ) {
    }

    public function getVariable(): Variable
    {
        return $this->variable;
    }

    public function getDimFetchExpr(): Expr
    {
        return $this->dimFetchExpr;
    }
}
