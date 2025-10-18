<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\YieldDataProviderRector\Fixture;

use PHPUnit\Framework\TestCase;

final class UseDataProviderTest extends TestCase
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
            ['value5', 'value6'],
            ['value7', 'value8'],
        ];
    }

}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\YieldDataProviderRector\Fixture;

use PHPUnit\Framework\TestCase;

final class UseDataProviderTest extends TestCase
{
    #[\PHPUnit\Framework\Attributes\DataProvider('dataProvider')]
    public function test(string $val1, string $val2): void
    {
    }

    public static function dataProvider(): \Iterator
    {
        yield ['value1', 'value2'];
        yield ['value3', 'value4'];
        yield ['value5', 'value6'];
        yield ['value7', 'value8'];
    }

}

?>
