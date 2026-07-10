<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\AssertClassToThisAssertRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipSelfCall extends TestCase
{
    public function testMe()
    {
        self::assertSame(1, 1);
    }
}
