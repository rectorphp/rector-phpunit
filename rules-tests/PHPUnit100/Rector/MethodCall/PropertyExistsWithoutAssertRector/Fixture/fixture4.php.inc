<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\MethodCall\AssertPropertyExistsRector\Fixture;

final class MyTest4 extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $this->assertObjectHasAttribute($property, $object);
        $this->assertObjectNotHasAttribute($property, $object);
        $this->assertObjectHasAttribute($property[0], $object);
        $this->assertObjectNotHasAttribute($property[1], $object);
        $this->assertObjectHasAttribute($property->name, $object);
        $this->assertObjectNotHasAttribute($property[1]->name, $object);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\MethodCall\AssertPropertyExistsRector\Fixture;

final class MyTest4 extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $this->assertTrue(property_exists($object, $property));
        $this->assertFalse(property_exists($object, $property));
        $this->assertTrue(property_exists($object, $property[0]));
        $this->assertFalse(property_exists($object, $property[1]));
        $this->assertTrue(property_exists($object, $property->name));
        $this->assertFalse(property_exists($object, $property[1]->name));
    }
}

?>
