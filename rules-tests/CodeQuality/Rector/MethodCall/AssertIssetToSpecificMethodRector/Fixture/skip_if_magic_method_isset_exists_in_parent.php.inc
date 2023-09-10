<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertIssetToSpecificMethodRector\Fixture;

// parent class not loaded
final class CustomIsset2 extends SomeAbstractClass {
}

final class SkipCustomIsset2 extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $foo = new \Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertIssetToSpecificMethodRector\Fixture\CustomIsset2();
        $this->assertTrue(isset($foo->bar));
    }
}
