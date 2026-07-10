<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\AssertClassToThisAssertRector\Fixture;

use PHPUnit\Framework\Assert;

final class SkipNonTestClass
{
    public function run()
    {
        Assert::assertSame(1, 1);
    }
}
