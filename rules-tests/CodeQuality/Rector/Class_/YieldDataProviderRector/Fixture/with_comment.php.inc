<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\YieldDataProviderRector\Fixture;

use PHPUnit\Framework\TestCase;

final class WithComment extends TestCase
{
    #[\PHPUnit\Framework\Attributes\DataProvider('dataProvider')]
    public function test(string $filePath): void
    {
    }

    /**
     * some comment
     */
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

final class WithComment extends TestCase
{
    #[\PHPUnit\Framework\Attributes\DataProvider('dataProvider')]
    public function test(string $filePath): void
    {
    }

    /**
     * some comment
     */
    public static function dataProvider(): \Iterator
    {
        yield ['<?php implode(\'\', $foo, );', '<?php implode($foo, );'];
        yield ['<?php implode(\'\', $foo, );', '<?php implode($foo, );'];
    }
}

?>
