<?php

declare(strict_types=1);

namespace Rector\PHPUnit\CodeQuality\ValueObject;

final readonly class VariableNameToType
{
    public function __construct(
        private string $variableName,
        private string $objectType
    ) {
    }

    public function getVariableName(): string
    {
        return $this->variableName;
    }

    public function getObjectType(): string
    {
        return $this->objectType;
    }
}
