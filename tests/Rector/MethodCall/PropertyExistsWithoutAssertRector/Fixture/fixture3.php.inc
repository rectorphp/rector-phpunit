<?php

namespace Rector\PHPUnit\Tests\Rector\MethodCall\AssertPropertyExistsRector\Fixture;

final class MyTest3 extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $this->assertObjectHasAttribute('property', $object->data);
        $this->assertObjectNotHasAttribute('property', $object->data);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\Rector\MethodCall\AssertPropertyExistsRector\Fixture;

final class MyTest3 extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $this->assertTrue(property_exists($object->data, 'property'));
        $this->assertFalse(property_exists($object->data, 'property'));
    }
}

?>
