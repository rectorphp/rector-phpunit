<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\YieldDataProviderRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipMultipleYieldFrom extends TestCase
{
    #[\PHPUnit\Framework\Attributes\DataProvider('dataProvider')]
    public function test(string $val1, string $val2): void
    {
    }

    public static function dataProvider(): iterable
    {
        yield from [
            ['value1', 'value2'],
            ['value3', 'value4'],
        ];
        yield from [
            ['value5', 'value6'],
            ['value7', 'value8'],
        ];
    }

}

?>
