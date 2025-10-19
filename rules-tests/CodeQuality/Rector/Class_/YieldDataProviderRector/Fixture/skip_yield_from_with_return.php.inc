<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\YieldDataProviderRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipYieldFromExprWithReturn extends TestCase
{
    #[\PHPUnit\Framework\Attributes\DataProvider('dataProvider')]
    public function test(string $val1, string $val2): void
    {
    }

    public static function dataProvider(): iterable
    {
        yield from [
            ['value3', 'value4'],
            ['value5', 'value6'],
            ['value7', 'value8'],
        ];

        if (PHP_VERSION_ID < 80100) {
            return;
        }

        return [['value1', 'value2']];
    }

}

?>
