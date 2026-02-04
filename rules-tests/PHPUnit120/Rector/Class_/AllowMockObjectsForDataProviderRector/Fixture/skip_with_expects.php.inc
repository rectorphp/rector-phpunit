<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\Class_\AllowMockObjectsForDataProviderRector\Fixture;

use PHPUnit\Framework\Attributes\DataProvider;
use PHPUnit\Framework\TestCase;

final class SkipWithExpects extends TestCase
{
    #[DataProvider('someDataProvider')]
    public function test()
    {
        $someMock = $this->createMock(\stdClass::class);
        $someMock->expects($this->once())->method('some')->willReturn(true);
    }

    public static function someDataProvider(): iterable
    {
        yield [1];
        yield [2];
        yield [3];
    }
}
