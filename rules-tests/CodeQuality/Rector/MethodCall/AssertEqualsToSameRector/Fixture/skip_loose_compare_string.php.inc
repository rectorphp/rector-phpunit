<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertEqualsToSameRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipLooseCompareString extends TestCase
{
    public function test()
    {
        $this->assertEquals(1, '1');
    }
}
