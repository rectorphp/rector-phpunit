<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\PreferPHPUnitThisCallRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipInStaticArrowFunction extends TestCase
{
    public function testMe()
    {
        static fn() => self::assertSame(1, 1);
    }
}

?>