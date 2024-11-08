<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\MethodCall\AssertIssetToAssertObjectHasPropertyRector\Fixture;

use ArrayAccess;
use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\PHPUnit100\Rector\MethodCall\AssertIssetToAssertObjectHasPropertyRector\Source\WithMagicGet;

final class SkipWithMagicGet extends TestCase
{
    public function test()
    {
        $object = new WithMagicGet();
        $this->assertTrue(isset($object->one));
    }
}
