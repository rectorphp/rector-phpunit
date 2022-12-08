<?php

declare(strict_types=1);

namespace Rector\PHPUnit\ValueObject;

final class AnnotationWithValueToAttribute
{
    /**
     * @param array<mixed, mixed> $valueMap
     */
    public function __construct(
        private readonly string $annotationName,
        private readonly string $attributeClass,
        private readonly array $valueMap
    ) {
    }

    public function getAnnotationName(): string
    {
        return $this->annotationName;
    }

    public function getAttributeClass(): string
    {
        return $this->attributeClass;
    }

    /**
     * @return array<mixed, mixed>
     */
    public function getValueMap(): array
    {
        return $this->valueMap;
    }
}
