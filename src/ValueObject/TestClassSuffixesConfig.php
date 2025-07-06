<?php

declare(strict_types=1);

namespace Rector\PHPUnit\ValueObject;

final readonly class TestClassSuffixesConfig
{
    /**
     * @param string[] $suffixes
     */
    public function __construct(
        private array $suffixes = ['Test', 'TestCase']
    ) {
    }

    /**
     * @return string[]
     */
    public function getSuffixes(): array
    {
        return $this->suffixes;
    }
}
