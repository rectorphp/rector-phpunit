<?php

namespace Rector\PHPUnit\Tests\Transform\Rector\AssertEqualsOrAssertSameFloatParameterToSpecificMethodsTypeRector\Fixture;

use PHPUnit\Framework\TestCase;

class MyTest1 extends TestCase
{
    public function test()
    {
        $value = 10.20001;
        $this->assertSame(10.20, $value);
        $this->assertEquals(10.20, $value);
        $this->assertEquals(10.200, $value);
        $this->assertEquals('10.20', $value);
        $this->assertSame(10.28, $value);
        $this->assertEquals(10.2, $value);
        $this->assertEquals(10, $value);
        $this->assertSame(10, $value);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\Transform\Rector\AssertEqualsOrAssertSameFloatParameterToSpecificMethodsTypeRector\Fixture;

use PHPUnit\Framework\TestCase;

class MyTest1 extends TestCase
{
    public function test()
    {
        $value = 10.20001;
        $this->assertEqualsWithDelta(10.20, $value, 0.01);
        $this->assertEqualsWithDelta(10.20, $value, 0.01);
        $this->assertEqualsWithDelta(10.200, $value, 0.001);
        $this->assertEquals('10.20', $value);
        $this->assertEqualsWithDelta(10.28, $value, 0.01);
        $this->assertEqualsWithDelta(10.2, $value, 0.1);
        $this->assertEquals(10, $value);
        $this->assertSame(10, $value);
    }
}

?>
