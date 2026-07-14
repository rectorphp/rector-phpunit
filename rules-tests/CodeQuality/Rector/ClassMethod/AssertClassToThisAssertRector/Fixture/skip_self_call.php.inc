<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\AssertClassToThisAssertRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipSelfCall extends TestCase
{
    public function testMe()
    {
        self::assertSame(1, 1);
    }
}
