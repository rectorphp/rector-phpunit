<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\MethodCall\PropertyExistsWithoutAssertRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AssertHasAttribute extends TestCase
{
    public function test()
    {
        $this->assertClassHasAttribute('property', 'stdClass');
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\MethodCall\PropertyExistsWithoutAssertRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AssertHasAttribute extends TestCase
{
    public function test()
    {
        $this->assertTrue(property_exists('stdClass', 'property'));
    }
}

?>
