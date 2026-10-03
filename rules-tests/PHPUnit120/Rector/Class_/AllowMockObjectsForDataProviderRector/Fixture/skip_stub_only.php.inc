<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\Class_\AllowMockObjectsForDataProviderRector\Fixture;

use PHPUnit\Framework\Attributes\DataProvider;
use PHPUnit\Framework\TestCase;

final class SkipStubOnly extends TestCase
{
    #[DataProvider('someDataProvider')]
    public function test(int $value)
    {
        $someStub = $this->createStub(\Countable::class);
        $someStub->method('count')->willReturn($value);

        $this->assertSame($value, $someStub->count());
    }

    public static function someDataProvider(): iterable
    {
        yield [1];
        yield [2];
    }
}
