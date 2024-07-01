<?php

namespace Rector\PHPUnit\Tests\PHPUnit110\Rector\MethodCall\NamedArgumentForDataProviderRector\Fixture;

use PHPUnit\Framework\TestCase;

final class TestWithMultipleDataProvidersForASingleTest extends TestCase
{
    public static function dataProviderA(): array
    {
        return [
            [
                'keyA' => true,
                'keyB' => false,
            ]
        ];
    }
    public static function dataProviderB(): array
    {
        return [
            [
                'keyA' => true,
                'keyB' => false,
            ]
        ];
    }

    #[\PHPUnit\Framework\Attributes\DataProvider('dataProviderA')]
    #[\PHPUnit\Framework\Attributes\DataProvider('dataProviderB')]
    public function testFilter(bool $changeToKeyA, bool $changeToKeyB): void
    {
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit110\Rector\MethodCall\NamedArgumentForDataProviderRector\Fixture;

use PHPUnit\Framework\TestCase;

final class TestWithMultipleDataProvidersForASingleTest extends TestCase
{
    public static function dataProviderA(): array
    {
        return [
            [
                'changeToKeyA' => true,
                'changeToKeyB' => false,
            ]
        ];
    }
    public static function dataProviderB(): array
    {
        return [
            [
                'changeToKeyA' => true,
                'changeToKeyB' => false,
            ]
        ];
    }

    #[\PHPUnit\Framework\Attributes\DataProvider('dataProviderA')]
    #[\PHPUnit\Framework\Attributes\DataProvider('dataProviderB')]
    public function testFilter(bool $changeToKeyA, bool $changeToKeyB): void
    {
    }
}

?>
