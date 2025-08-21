<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\MatchAssertEqualsExpectedTypeRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipArgumentLess extends TestCase
{
    public function test()
    {
        $this->assertSame(1);
    }
}
