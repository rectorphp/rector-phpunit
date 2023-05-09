<?php

declare(strict_types=1);

namespace Rector\PHPUnit\ValueObject;

use PhpParser\Node\Arg;
use Webmozart\Assert\Assert;

final class DataProviderClassMethodRecipe
{
    /**
     * @param Arg[] $args
     */
    public function __construct(
        private readonly string $methodName,
        private readonly array $args
    ) {
        Assert::allIsInstanceOf($args, Arg::class);
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
