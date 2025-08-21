<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\MatchAssertSameExpectedTypeRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipFirstClassCallable extends TestCase
{
    public function test()
    {
        $this->assertSame(...);
    }
}
