<?php

declare(strict_types=1);

namespace Rector\PHPUnit\ValueObject;

final readonly class FunctionNameWithAssertMethods
{
    public function __construct(
        private string $functionName,
        private string $assetMethodName,
        private string $notAssertMethodName
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
