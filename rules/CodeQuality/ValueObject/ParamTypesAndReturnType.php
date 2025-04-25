<?php

declare(strict_types=1);

namespace Rector\PHPUnit\CodeQuality\ValueObject;

use PHPStan\Type\Type;

final readonly class ParamTypesAndReturnType
{
    /**
     * @param Type[] $paramTypes
     */
    public function __construct(
        private array $paramTypes,
        private ?Type $returnType
    ) {
    }

    /**
     * @return Type[]
     */
    public function getParamTypes(): array
    {
        return $this->paramTypes;
    }

    public function getReturnType(): ?Type
    {
        return $this->returnType;
    }
}
