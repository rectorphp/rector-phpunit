<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\YieldDataProviderRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipYieldFromExpr extends TestCase
{
    #[\PHPUnit\Framework\Attributes\DataProvider('dataProvider')]
    public function test(string $val1, string $val2): void
    {
    }

    public static function dataProvider(): iterable
    {
        yield from self::someData();
    }

    public static function someData(): iterable
    {
        yield ['value1', 'value2'];
        yield ['value3', 'value4'];
        yield ['value5', 'value6'];
        yield ['value7', 'value8'];
    }
}

?>
