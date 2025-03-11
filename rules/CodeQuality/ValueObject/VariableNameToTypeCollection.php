<?php

declare(strict_types=1);

namespace Rector\PHPUnit\CodeQuality\ValueObject;

final class VariableNameToTypeCollection
{
    /**
     * @param VariableNameToType[] $variableNameToType
     */
    public function __construct(
        private array $variableNameToType
    ) {
    }
}
