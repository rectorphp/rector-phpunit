<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\MethodCall\AssertIssetToAssertObjectHasPropertyRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SomeIssetToProperty extends TestCase
{
    public function test()
    {
        $object = new \stdClass();
        $this->assertTrue(isset($object->someProperty));
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\MethodCall\AssertIssetToAssertObjectHasPropertyRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SomeIssetToProperty extends TestCase
{
    public function test()
    {
        $object = new \stdClass();
        $this->assertObjectHasProperty('someProperty', $object);
    }
}

?>
