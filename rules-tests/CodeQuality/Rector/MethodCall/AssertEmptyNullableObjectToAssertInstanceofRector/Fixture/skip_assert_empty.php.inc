<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertEmptyNullableObjectToAssertInstanceofRector\Fixture;

use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertEmptyNullableObjectToAssertInstanceofRector\Source\SomeTypeObject;
use PHPUnit\Framework\TestCase;

final class SkipAssertEmpty extends TestCase
{
    public function test()
    {
        if (mt_rand(0, 1)) {
            $someObject = null;
        } else {
            $someObject = new SomeTypeObject();
        }

        $this->assertEmpty($someObject);
    }
}

?>
