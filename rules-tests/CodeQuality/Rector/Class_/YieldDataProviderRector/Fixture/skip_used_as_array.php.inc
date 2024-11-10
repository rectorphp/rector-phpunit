<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\YieldDataProviderRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipUsedAsArray extends TestCase
{
    #[\PHPUnit\Framework\Attributes\DataProvider('provideDataForProvider')]
    public function test(string $filePath): void
    {
    }

    public static function provideDataForProvider()
    {
        return [
            ['<?php implode("", $foo, );', '<?php implode($foo, "", );']
        ];
    }

    public function testOther()
    {
        $firstData = self::provideDataForProvider()[0];
    }
}
