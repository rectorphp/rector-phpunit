<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\MethodCall\PropertyExistsWithoutAssertRector\Fixture;

use PHPUnit\Framework\TestCase;

final class MyPropertyExistsWithoutAssertRectorTest extends TestCase
{
    public function test()
    {
        $this->assertClassHasStaticAttribute('property', 'stdClass');
        $this->assertClassHasStaticAttribute('property', stdClass::class);
        $this->classHasStaticAttribute('property', stdClass::class, 'message');
        $this->assertClassNotHasStaticAttribute('property', 'Namespaced\stdClass', 'message');
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\MethodCall\PropertyExistsWithoutAssertRector\Fixture;

use PHPUnit\Framework\TestCase;

final class MyPropertyExistsWithoutAssertRectorTest extends TestCase
{
    public function test()
    {
        $this->assertTrue(property_exists('stdClass', 'property'));
        $this->assertTrue(property_exists(stdClass::class, 'property'));
        $this->assertTrue(property_exists(stdClass::class, 'property'), 'message');
        $this->assertFalse(property_exists('Namespaced\stdClass', 'property'), 'message');
    }
}

?>
