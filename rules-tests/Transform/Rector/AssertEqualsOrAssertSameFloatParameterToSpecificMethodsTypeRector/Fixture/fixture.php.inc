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
        $this->assertEqualsWithDelta(10.20, $value, PHP_FLOAT_EPSILON);
        $this->assertEqualsWithDelta(10.20, $value, PHP_FLOAT_EPSILON);
        $this->assertEqualsWithDelta(10.200, $value, PHP_FLOAT_EPSILON);
        $this->assertEquals('10.20', $value);
        $this->assertEqualsWithDelta(10.28, $value, PHP_FLOAT_EPSILON);
        $this->assertEqualsWithDelta(10.2, $value, PHP_FLOAT_EPSILON);
        $this->assertEquals(10, $value);
        $this->assertSame(10, $value);
    }
}

?>
