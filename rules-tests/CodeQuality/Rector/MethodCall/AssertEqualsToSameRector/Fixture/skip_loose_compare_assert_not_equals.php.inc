<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertEqualsToSameRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipLooseCompareAssertNotEquals extends TestCase
{
    public function test(float $float)
    {
        $this->assertNotEquals(1, $float);
    }
}
