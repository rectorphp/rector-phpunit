<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\AssertClassToThisAssertRector\Fixture;

use PHPUnit\Framework\Assert;
use PHPUnit\Framework\TestCase;

final class SkipStaticClosure extends TestCase
{
    public function testMe()
    {
        static fn() => Assert::assertSame(1, 1);
    }
}
