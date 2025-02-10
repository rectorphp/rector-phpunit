<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertCountWithZeroToAssertEmptyRector\Fixture;

final class SkipUnionType extends \PHPUnit\Framework\TestCase
{
    public function test($something)
    {
        foreach ([true, false] as $value) {
            $count = (int) $value;
            $this->assertCount($count, $something);
        }
    }
}
