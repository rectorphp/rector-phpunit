<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\Class_\StaticDataProviderClassMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipAlreadyStatic extends TestCase
{
    /**
     * @dataProvider provideData()
     */
    public function test()
    {
    }

    public static function provideData()
    {
        yield [1];
    }
}
