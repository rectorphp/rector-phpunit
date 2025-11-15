<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\MethodCall\PropertyExistsWithoutAssertRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AssertObjectHasAttribute extends TestCase
{
    public function test(object $someObject)
    {
        $this->assertObjectHasAttribute('property', $someObject);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\MethodCall\PropertyExistsWithoutAssertRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AssertObjectHasAttribute extends TestCase
{
    public function test(object $someObject)
    {
        $this->assertTrue(property_exists($someObject, 'property'));
    }
}

?>
