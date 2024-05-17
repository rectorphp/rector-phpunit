<?php

namespace Rector\PHPUnit\Tests\PHPUnit110\Rector\MethodCall\NamedArgumentForDataProviderRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SomeTestMissing extends TestCase
{
    public static function dataProviderArray(): array
    {
        return [
            [
                'keyA' => true,
                'keyB' => false,
            ],
        ];
    }

    #[\PHPUnit\Framework\Attributes\DataProvider('dataProviderArray')]
    public function testFilter(bool $changeToKeyA, bool $changeToKeyB): void
    {
    }

    #[\PHPUnit\Framework\Attributes\DataProvider('dataProviderArray')]
    public function testFilterOnce(bool $changeToKeyA): void
    {
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit110\Rector\MethodCall\NamedArgumentForDataProviderRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SomeTestMissing extends TestCase
{
    public static function dataProviderArray(): array
    {
        return [
            [
                'changeToKeyA' => true,
                'changeToKeyB' => false,
            ],
        ];
    }

    #[\PHPUnit\Framework\Attributes\DataProvider('dataProviderArray')]
    public function testFilter(bool $changeToKeyA, bool $changeToKeyB): void
    {
    }

    #[\PHPUnit\Framework\Attributes\DataProvider('dataProviderArray')]
    public function testFilterOnce(bool $changeToKeyA): void
    {
    }
}

?>
