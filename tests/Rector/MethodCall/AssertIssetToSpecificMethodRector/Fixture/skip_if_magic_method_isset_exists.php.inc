<?php

namespace Rector\PHPUnit\Tests\Rector\MethodCall\AssertIssetToSpecificMethodRector\Fixture;

final class CustomIsset {
    public function __isset($property) {
        return false;
    }
}

final class SkipCustomIsset extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $foo = new CustomIsset();
        $this->assertTrue(isset($foo->bar));
    }
}

?>
