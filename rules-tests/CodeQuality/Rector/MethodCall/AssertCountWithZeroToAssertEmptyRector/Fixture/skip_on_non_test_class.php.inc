<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertCountWithZeroToAssertEmptyRector\Fixture;

use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertCountWithZeroToAssertEmptyRector\Source\Collection;

final class SkipOnNonTestClass
{
    public function test()
    {
        $collection = new Collection();
        $this->assertCount(0, $collection);
    }
}

?>
