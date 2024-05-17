<?php

namespace Rector\PHPUnit\Tests\PHPUnit110\Rector\MethodCall\NamedArgumentForDataProviderRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SomeTestNumeric extends TestCase
{
    public static function dataProviderArray(): array
    {
        return [
            [
                true,
                false,
            ],
        ];
    }

    #[\PHPUnit\Framework\Attributes\DataProvider('dataProviderArray')]
    public function testFilter(bool $changeToKeyA, bool $changeToKeyB): void
    {
    }
}
?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit110\Rector\MethodCall\NamedArgumentForDataProviderRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SomeTestNumeric extends TestCase
{
    public static function dataProviderArray(): array
    {
        return [
            [
                true,
                false,
            ],
        ];
    }

    #[\PHPUnit\Framework\Attributes\DataProvider('dataProviderArray')]
    public function testFilter(bool $changeToKeyA, bool $changeToKeyB): void
    {
    }
}
?>
