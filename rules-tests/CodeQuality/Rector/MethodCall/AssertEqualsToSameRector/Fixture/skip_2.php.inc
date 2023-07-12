<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertEqualsToSameRector\Fixture;

use PHPUnit\Framework\TestCase;

final class MySkipTest2 extends TestCase
{
    public function test()
    {
        $null = null;
        $expectedNull = null;
        self::assertEquals($expectedNull, $null);

        $bool = true;
        $expectedBool = true;
        self::assertEquals($expectedBool, $bool);
    }
}
