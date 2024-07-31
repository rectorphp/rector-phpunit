<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\MethodCall\RemoveSetMethodsMethodCallRector\Fixture;

use PHPUnit\Framework\TestCase;
use PHPUnit100\Rector\MethodCall\RemoveSetMethodsMethodCallRector\Source\SomeClassWithMagicMethods;

final class KeepIfMethodIsMagic extends TestCase
{
    public function test()
    {
        $someMock = $this->getMockBuilder(SomeClassWithMagicMethods::class)
            ->setMethods(['normalMethod', 'magicMethod'])
            ->getMock();
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\MethodCall\RemoveSetMethodsMethodCallRector\Fixture;

use PHPUnit\Framework\TestCase;
use PHPUnit100\Rector\MethodCall\RemoveSetMethodsMethodCallRector\Source\SomeClassWithMagicMethods;

final class KeepIfMethodIsMagic extends TestCase
{
    public function test()
    {
        $someMock = $this->getMockBuilder(SomeClassWithMagicMethods::class)
            ->addMethods(['magicMethod'])
            ->getMock();
    }
}

?>
