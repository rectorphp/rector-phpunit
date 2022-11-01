<?php

namespace Rector\PHPUnit\Tests\Rector\MethodCall\AssertEqualsToSameRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AssertNotEqualsEmptyArray extends TestCase
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

namespace Rector\PHPUnit\Tests\Rector\MethodCall\AssertEqualsToSameRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AssertNotEqualsEmptyArray extends TestCase
{
    public function test()
    {
        $array = [];
        $expectedArray = [];
        $this->assertSame($array, $expectedArray);
    }
}

?>
