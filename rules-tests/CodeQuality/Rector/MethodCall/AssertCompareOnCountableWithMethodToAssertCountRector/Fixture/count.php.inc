<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertCompareOnCountableWithMethodToAssertCountRector\Fixture;

use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertCompareOnCountableWithMethodToAssertCountRector\Source\Collection;

final class Count extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $collection = new Collection();
        $this->assertSame(5, $collection->count());
        $this->assertEquals(5, $collection->count());
        \PHPUnit\Framework\TestCase::assertSame(5, $collection->count());
        self::assertSame(5, $collection->count());
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertCompareOnCountableWithMethodToAssertCountRector\Fixture;

use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertCompareOnCountableWithMethodToAssertCountRector\Source\Collection;

final class Count extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $collection = new Collection();
        $this->assertCount(5, $collection);
        $this->assertCount(5, $collection);
        \PHPUnit\Framework\TestCase::assertCount(5, $collection);
        self::assertCount(5, $collection);
    }
}

?>
