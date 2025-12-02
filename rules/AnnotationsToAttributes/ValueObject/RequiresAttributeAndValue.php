<?php

declare(strict_types=1);

namespace Rector\PHPUnit\AnnotationsToAttributes\ValueObject;

use Rector\PHPUnit\Enum\PHPUnitAttribute;

final readonly class RequiresAttributeAndValue
{
    /**
     * @param PHPUnitAttribute::* $attributeClass
     * @param string[] $value
     */
    public function __construct(
        private string $attributeClass,
        private array $value,
    ) {
    }

    /**
     * @return PHPUnitAttribute::*
     */
    public function getAttributeClass(): string
    {
        return $this->attributeClass;
    }

    /**
     * @return string[]
     */
    public function getValue(): array
    {
        return $this->value;
    }
}
