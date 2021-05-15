<?php

declare(strict_types=1);

namespace Rector\PHPUnit\ValueObject;

use PhpParser\Node\Expr\Variable;
use PHPStan\Type\Type;

final class ParamAndArg
{
    public function __construct(
        private Variable $variable,
        private ?\PHPStan\Type\Type $type
    ) {
    }

    public function getVariable(): Variable
    {
        return $this->variable;
    }

    public function getType(): ?Type
    {
        return $this->type;
    }
}
