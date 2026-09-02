<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertEmptyNullableObjectToAssertInstanceofRector\Fixture;

use CodeQuality\Rector\MethodCall\AssertEmptyNullableObjectToAssertInstanceofRector\Source\SomeTypeObject;
use PHPUnit\Framework\TestCase;

final class KeepCustomMessage extends TestCase
{
    public function test()
    {
        $someObject = mt_rand(0, 1) ? new SomeTypeObject() : null;

        $this->assertNotNull($someObject, 'some message');
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

        $this->assertInstanceOf(\CodeQuality\Rector\MethodCall\AssertEmptyNullableObjectToAssertInstanceofRector\Source\SomeTypeObject::class, $someObject, 'some message');
    }
}

?>
