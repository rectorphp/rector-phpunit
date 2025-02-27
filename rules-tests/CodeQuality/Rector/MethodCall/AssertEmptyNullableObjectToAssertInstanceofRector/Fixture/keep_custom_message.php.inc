<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertEmptyNullableObjectToAssertInstanceofRector\Fixture;

use CodeQuality\Rector\MethodCall\AssertEmptyNullableObjectToAssertInstanceofRector\Source\SomeTypeObject;
use PHPUnit\Framework\TestCase;

final class KeepCustomMessage extends TestCase
{
    public function test()
    {
        $someObject = mt_rand(0, 1) ? new SomeTypeObject() : null;

        $this->assertNull($someObject, 'some message');
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertEmptyNullableObjectToAssertInstanceofRector\Fixture;

use CodeQuality\Rector\MethodCall\AssertEmptyNullableObjectToAssertInstanceofRector\Source\SomeTypeObject;
use PHPUnit\Framework\TestCase;

final class KeepCustomMessage extends TestCase
{
    public function test()
    {
        $someObject = mt_rand(0, 1) ? new SomeTypeObject() : null;

        $this->assertNotInstanceOf(\CodeQuality\Rector\MethodCall\AssertEmptyNullableObjectToAssertInstanceofRector\Source\SomeTypeObject::class, $someObject, 'some message');
    }
}

?>
