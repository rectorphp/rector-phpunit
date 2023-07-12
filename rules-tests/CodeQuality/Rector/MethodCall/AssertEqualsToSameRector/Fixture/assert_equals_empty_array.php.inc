<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertEqualsToSameRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AssertEqualsEmptyArray extends TestCase
{
    public function test()
    {
        $array = [];
        $expectedArray = [];
        $this->assertEquals($array, $expectedArray);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertEqualsToSameRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AssertEqualsEmptyArray extends TestCase
{
    public function test()
    {
        $array = [];
        $expectedArray = [];
        $this->assertSame($array, $expectedArray);
    }
}

?>
