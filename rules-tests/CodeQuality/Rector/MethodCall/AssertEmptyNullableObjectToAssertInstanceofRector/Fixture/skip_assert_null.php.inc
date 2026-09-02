<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertEmptyNullableObjectToAssertInstanceofRector\Fixture;

use CodeQuality\Rector\MethodCall\AssertEmptyNullableObjectToAssertInstanceofRector\Source\SomeTypeObject;
use PHPUnit\Framework\TestCase;

final class SkipAssertNull extends TestCase
{
    public function test()
    {
        $someObject = mt_rand(0, 1) ? new SomeTypeObject() : null;

        $this->assertNull($someObject);
    }
}

?>
