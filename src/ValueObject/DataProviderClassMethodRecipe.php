<?php

declare(strict_types=1);

namespace Rector\PHPUnit\ValueObject;

use PhpParser\Node\Arg;

final class DataProviderClassMethodRecipe
{
    /**
     * @param Arg[] $args
     */
    public function __construct(
        private readonly string $methodName,
        private readonly array $args
    ) {
    }

    public function getMethodName(): string
    {
        return $this->methodName;
    }

    /**
     * @return Arg[]
     */
    public function getArgs(): array
    {
        return $this->args;
    }
}
