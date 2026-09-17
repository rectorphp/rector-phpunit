<?php

declare(strict_types=1);

namespace Rector\PHPUnit\CodeQuality\ValueObject;

use PHPStan\Type\IntersectionType;

final readonly class MockedMethod
{
    public function __construct(
        private string $methodName,
        private IntersectionType $intersectionType,
    ) {
    }

    public function getMethodName(): string
    {
        return $this->methodName;
    }

    public function getCallerType(): IntersectionType
    {
        return $this->intersectionType;
    }
}
