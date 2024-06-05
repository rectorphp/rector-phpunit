<?php

namespace Rector\PHPUnit\Tests\PHPUnit110\Rector\MethodCall\NamedArgumentForDataProviderRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SomeTestYield extends TestCase
{
    public static function dataProvider(): Generator
    {
        yield [
            'keyA' => true,
            'keyB' => false,
        ];
    }

    #[\PHPUnit\Framework\Attributes\DataProvider('dataProvider')]
    public function testFilter(bool $changeToKeyA, bool $changeToKeyB): void
    {
    }
}
?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit110\Rector\MethodCall\NamedArgumentForDataProviderRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SomeTestYield extends TestCase
{
    public static function dataProvider(): Generator
    {
        yield [
            'changeToKeyA' => true,
            'changeToKeyB' => false,
        ];
    }

    #[\PHPUnit\Framework\Attributes\DataProvider('dataProvider')]
    public function testFilter(bool $changeToKeyA, bool $changeToKeyB): void
    {
    }
}
?>
