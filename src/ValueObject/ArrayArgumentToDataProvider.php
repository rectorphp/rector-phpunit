<?php

declare(strict_types=1);

namespace Rector\PHPUnit\ValueObject;

use PHPStan\Type\ObjectType;

final class ArrayArgumentToDataProvider
{
    public function __construct(
        private string $class,
        private string $oldMethod,
        private string $newMethod,
        private string $variableName
    ) {
    }

    public function getObjectType(): ObjectType
    {
        return new ObjectType($this->class);
    }

    public function getOldMethod(): string
    {
        return $this->oldMethod;
    }

    public function getNewMethod(): string
    {
        return $this->newMethod;
    }

    public function getVariableName(): string
    {
        return $this->variableName;
    }
}
