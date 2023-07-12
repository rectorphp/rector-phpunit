<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\MethodCall\AssertPropertyExistsRector\Fixture;

use PHPUnit\Framework\TestCase;

final class MyTest1 extends TestCase
{
    public function test()
    {
        $this->assertClassHasAttribute('property', 'stdClass');
        $this->assertClassNotHasAttribute('property', 'Namespaced\stdClass', 'message');
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\MethodCall\AssertPropertyExistsRector\Fixture;

use PHPUnit\Framework\TestCase;

final class MyTest1 extends TestCase
{
    public function test()
    {
        $this->assertTrue(property_exists(new \stdClass(), 'property'));
        $this->assertFalse(property_exists(new \Namespaced\stdClass(), 'property'), 'message');
    }
}

?>
