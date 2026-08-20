<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\MatchAssertSameExpectedTypeRector\Source;

final class Criteria
{
    private ?int $typeId = null;

    private ?bool $anyType = null;

    public function setTypeId(int $typeId): self
    {
        $this->typeId = $typeId;
        $this->anyType = null;

        return $this;
    }

    public function setAnyType(bool $anyType): self
    {
        $this->anyType = $anyType;
        $this->typeId = null;

        return $this;
    }

    public function getType(): int|string|null
    {
        return $this->anyType ? 'Any' : $this->typeId;
    }
}
