<?php

namespace Rector\PHPUnit\Tests\PHPUnit110\Rector\MethodCall\NamedArgumentForDataProviderRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SomeTestSkipChangedOrder extends TestCase
{
    public static function dataProvider(): Generator
    {
        yield [
            'keyB' => false,
            'keyA' => true,
        ];
    }

    #[\PHPUnit\Framework\Attributes\DataProvider('dataProvider')]
    public function testFilter(bool $keyA, bool $keyB): void
    {
    }
}
?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit110\Rector\MethodCall\NamedArgumentForDataProviderRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SomeTestSkipChangedOrder extends TestCase
{
    public static function dataProvider(): Generator
    {
        yield [
            'keyB' => false,
            'keyA' => true,
        ];
    }

    #[\PHPUnit\Framework\Attributes\DataProvider('dataProvider')]
    public function testFilter(bool $keyA, bool $keyB): void
    {
    }
}
?>
