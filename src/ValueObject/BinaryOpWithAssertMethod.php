<?php

declare(strict_types=1);

namespace Rector\PHPUnit\ValueObject;

final class BinaryOpWithAssertMethod
{
    public function __construct(
        private readonly string $binaryOpClass,
        private readonly string $assetMethodName,
        private readonly string $notAssertMethodName
    ) {
    }

    public function getBinaryOpClass(): string
    {
        return $this->binaryOpClass;
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
