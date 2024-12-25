<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertEqualsToSameRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipLooseCompare2 extends TestCase
{
    public function test()
    {
        $this->assertEquals(1.0, 1);
    }
}
