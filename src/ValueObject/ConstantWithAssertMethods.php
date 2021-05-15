<?php

declare(strict_types=1);

namespace Rector\PHPUnit\ValueObject;

final class ConstantWithAssertMethods
{
    public function __construct(
        private string $constant,
        private string $assetMethodName,
        private string $notAssertMethodName
    ) {
    }

    public function getConstant(): string
    {
        return $this->constant;
    }

    public function getAssetMethodName(): string
    {
        return $this->assetMethodName;
    }

    public function getNotAssertMethodName(): string
    {
        return $this->notAssertMethodName;
    }
}
