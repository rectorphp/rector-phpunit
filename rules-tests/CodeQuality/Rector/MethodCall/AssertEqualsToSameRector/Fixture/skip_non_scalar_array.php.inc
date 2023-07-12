<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertEqualsToSameRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipNonScalarArray extends TestCase
{
    public function test($result, array $expectedArray)
    {
        $this->assertEquals($expectedArray, $result);
    }
}
