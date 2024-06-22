<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\MethodCall\AssertIssetToAssertObjectHasPropertyRector\Fixture;

final class CustomIsset
{
    public function __isset($property) {
        return false;
    }
}

final class SkipMagicIsset extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $foo = new CustomIsset();
        $this->assertTrue(isset($foo->bar));
    }
}
