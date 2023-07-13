<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertEqualsToSameRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AssertEqualsNonEmptyArray extends TestCase
{
    public function test()
    {
        $array = ['test'];
        $expectedArray = ['test'];
        $this->assertEquals($array, $expectedArray);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\MethodCall\AssertEqualsToSameRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AssertEqualsNonEmptyArray extends TestCase
{
    public function test()
    {
        $array = ['test'];
        $expectedArray = ['test'];
        $this->assertSame($array, $expectedArray);
    }
}

?>
