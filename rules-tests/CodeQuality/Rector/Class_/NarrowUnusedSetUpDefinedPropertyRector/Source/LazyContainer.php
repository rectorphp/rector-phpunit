<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\NarrowUnusedSetUpDefinedPropertyRector\Source;

final class LazyContainer
{
    /**
     * @param array<string, callable> $factories
     */
    public function __construct(
        private array $factories
    ) {
    }
}
