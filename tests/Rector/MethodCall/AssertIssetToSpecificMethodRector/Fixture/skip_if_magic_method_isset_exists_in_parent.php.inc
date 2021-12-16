<?php

namespace Rector\PHPUnit\Tests\Rector\MethodCall\AssertIssetToSpecificMethodRector\Fixture;

// parent class not loaded
final class CustomIsset2 extends SomeAbstractClass {
}

final class SkipCustomIsset2 extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $foo = new CustomIsset2();
        $this->assertTrue(isset($foo->bar));
    }
}

?>
