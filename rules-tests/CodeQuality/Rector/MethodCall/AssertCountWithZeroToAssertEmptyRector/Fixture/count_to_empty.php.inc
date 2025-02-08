<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertCountWithZeroToAssertEmptyRector\Fixture;

use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertCountWithZeroToAssertEmptyRector\Source\Collection;

final class CountToEmpty extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $collection = new Collection();
        $this->assertCount(0, $collection);
        $this->assertCount(0, $collection, 'message here!');
        $this->assertNotCount(0, $collection);
        $this->assertNotCount(0, $collection, 'message here!');
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertCountWithZeroToAssertEmptyRector\Fixture;

use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertCountWithZeroToAssertEmptyRector\Source\Collection;

final class CountToEmpty extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $collection = new Collection();
        $this->assertEmpty($collection);
        $this->assertEmpty($collection, 'message here!');
        $this->assertNotEmpty($collection);
        $this->assertNotEmpty($collection, 'message here!');
    }
}

?>
