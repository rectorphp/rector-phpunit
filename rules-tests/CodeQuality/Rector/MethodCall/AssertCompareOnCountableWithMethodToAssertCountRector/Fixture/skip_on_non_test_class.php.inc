<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertCompareOnCountableWithMethodToAssertCountRector\Fixture;

use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertCompareOnCountableWithMethodToAssertCountRector\Source\Collection;

final class SkipOnNonTestClass
{
    public function test()
    {
        $collection = new Collection();
        $this->assertSame(5, $collection->count());
        $this->assertEquals(5, $collection->count());
        self::assertSame(5, $collection->count());
    }
}

?>
