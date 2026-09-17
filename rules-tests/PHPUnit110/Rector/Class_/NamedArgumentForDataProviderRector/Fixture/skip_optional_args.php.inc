<?php

namespace Rector\PHPUnit\Tests\PHPUnit110\Rector\MethodCall\NamedArgumentForDataProviderRector\Fixture;

use PHPUnit\Framework\TestCase;

final class TestWithOptionalArguments extends TestCase
{
    public static function dataProvider(): Generator
    {
        yield [
            'keyA' => false,
            'keyC' => true,
        ];
    }

    #[\PHPUnit\Framework\Attributes\DataProvider('dataProvider')]
    public function testFilter(bool $keyA, bool $keyB = false, bool $keyC = false): void
    {
    }
}
?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit110\Rector\MethodCall\NamedArgumentForDataProviderRector\Fixture;

use PHPUnit\Framework\TestCase;

final class TestWithOptionalArguments extends TestCase
{
    public static function dataProvider(): Generator
    {
        yield [
            'keyA' => false,
            'keyC' => true,
        ];
    }

    #[\PHPUnit\Framework\Attributes\DataProvider('dataProvider')]
    public function testFilter(bool $keyA, bool $keyB = false, bool $keyC = false): void
    {
    }
}
?>
