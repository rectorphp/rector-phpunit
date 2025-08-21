<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\MatchAssertEqualsExpectedTypeRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipFirstClassCallable extends TestCase
{
    public function test()
    {
        $this->assertSame(...);
    }
}
