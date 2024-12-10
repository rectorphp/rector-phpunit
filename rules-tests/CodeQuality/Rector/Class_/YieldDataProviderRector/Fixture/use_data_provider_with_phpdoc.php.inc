<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\YieldDataProviderRector\Fixture;

use PHPUnit\Framework\TestCase;

final class UseDataProviderTestPhpdoc extends TestCase
{
    #[\PHPUnit\Framework\Attributes\DataProvider('dataProvider')]
    #[\PHPUnit\Framework\Attributes\DataProvider('provideDataForProvider')]
    public function test(string $filePath): void
    {
    }

    /** @return array<int, array<string>> */
    public static function provideDataForProvider()
    {
        return [
            ['<?php implode("", $foo, );', '<?php implode($foo, "", );']
        ];
    }

    /** @return list<array<string>> */
    public static function dataProvider()
    {
        return [
            ['<?php implode(\'\', $foo, );', '<?php implode($foo, );'],
            ['<?php implode(\'\', $foo, );', '<?php implode($foo, );']
        ];
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\YieldDataProviderRector\Fixture;

use PHPUnit\Framework\TestCase;

final class UseDataProviderTestPhpdoc extends TestCase
{
    #[\PHPUnit\Framework\Attributes\DataProvider('dataProvider')]
    #[\PHPUnit\Framework\Attributes\DataProvider('provideDataForProvider')]
    public function test(string $filePath): void
    {
    }

    /** @return \Iterator<int, array<string>> */
    public static function provideDataForProvider(): \Iterator
    {
        yield ['<?php implode("", $foo, );', '<?php implode($foo, "", );'];
    }

    /** @return \Iterator<int<0, max>, array<string>> */
    public static function dataProvider(): \Iterator
    {
        yield ['<?php implode(\'\', $foo, );', '<?php implode($foo, );'];
        yield ['<?php implode(\'\', $foo, );', '<?php implode($foo, );'];
    }
}

?>
