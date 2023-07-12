<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\PreferPHPUnitThisCallRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipReplaceInStaticCall extends TestCase
{
    public static function testMe()
    {
        self::assertSame(1, 1);
    }
}
