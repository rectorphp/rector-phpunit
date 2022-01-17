<?php

declare(strict_types=1);

namespace Rector\PHPUnit\ValueObject;

final class FunctionNameWithAssertMethods
{
    public function __construct(
        private readonly string $functionName,
        private readonly string $assetMethodName,
        private readonly string $notAssertMethodName
    ) {
    }

    public function getFunctionName(): string
    {
        return $this->functionName;
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
