<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\NarrowUnusedSetUpDefinedPropertyRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipPropertyUsedInClosure extends TestCase
{
    private array $dataSource;

    protected function setUp(): void
    {
        $this->dataSource = [1, 2, 3];

        $this->resolver = function () {
            return $this->dataSource;
        };
    }

    public function test()
    {
        $resolver = $this->resolver;
        $this->assertSame([1, 2, 3], $resolver());
    }
}
