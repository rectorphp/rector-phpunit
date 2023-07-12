<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertIssetToSpecificMethodRector\Fixture;

final class CustomSet {
    public function __set($property, $value) {
    }
}

final class FixCustomSet extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $foo = new CustomSet();
        $this->assertTrue(isset($foo->bar));
    }
}
?>
-----
<?php

namespace Rector\PHPUnit\Tests\Rector\MethodCall\AssertIssetToSpecificMethodRector\Fixture;

final class CustomSet {
    public function __set($property, $value) {
    }
}

final class FixCustomSet extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $foo = new \Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertIssetToSpecificMethodRector\Fixture\CustomSet();
        $this->assertObjectHasAttribute('bar', $foo);
    }
}
?>
