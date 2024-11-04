<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\NarrowUnusedSetUpDefinedPropertyRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipWithDefaultValue extends TestCase
{
    private array $item = [
        1, 2, 3,
    ];

    protected function setUp(): void
    {
        $value = sort($this->item);
    }

    public function test()
    {
        $this->assertTrue(true);
    }
}
