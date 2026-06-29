<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertIssetToSpecificMethodRector\Fixture;

use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertIssetToSpecificMethodRector\Source\SomeArrayAccessStore;

final class SkipArrayAccessObject extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $store = new SomeArrayAccessStore();

        $this->assertTrue(isset($store[$key]), 'message');
        $this->assertFalse(isset($store[$key]));
    }
}
