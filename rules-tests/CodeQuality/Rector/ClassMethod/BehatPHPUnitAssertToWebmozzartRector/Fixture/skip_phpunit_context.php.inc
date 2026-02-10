<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\BehatPHPUnitAssertToWebmozzartRector\Fixture;

use PHPUnit\Framework\Assert;
use PHPUnit\Framework\TestCase;

final class SkipPHPUnitContext extends TestCase
{
    public function testSomething()
    {
        Assert::assertSame('expected', 'given');

        Assert::assertStringContainsString('needle', 'haystack');
    }
}
