<?php

namespace Rector\PHPUnit\Tests\PHPUnit110\Rector\MethodCall\NamedArgumentForDataProviderRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SomeTestResolveVariable extends TestCase
{
    public static function dataProvider(): array
    {
        $unpack = [
            'dataProvider1' => [
                'a' => true,
                'b' => true,
            ],
        ];

        return [...$unpack];
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

final class SomeTestResolveVariable extends TestCase
{
    public static function dataProvider(): array
    {
        $unpack = [
            'dataProvider1' => [
                'changeToKeyA' => true,
                'changeToKeyB' => true,
            ],
        ];

        return [...$unpack];
    }

    #[\PHPUnit\Framework\Attributes\DataProvider('dataProvider')]
    public function testFilter(bool $changeToKeyA, bool $changeToKeyB): void
    {
    }
}
?>
