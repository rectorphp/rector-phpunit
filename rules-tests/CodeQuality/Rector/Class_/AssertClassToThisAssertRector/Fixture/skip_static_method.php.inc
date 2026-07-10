<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\AssertClassToThisAssertRector\Fixture;

use PHPUnit\Framework\Assert;
use PHPUnit\Framework\TestCase;

final class SkipStaticMethod extends TestCase
{
    public static function testMe()
    {
        Assert::assertSame(1, 1);
    }
}
