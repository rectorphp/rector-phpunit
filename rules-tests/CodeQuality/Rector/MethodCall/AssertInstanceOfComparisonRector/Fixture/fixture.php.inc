<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertInstanceOfComparisonRector\Fixture;

use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertInstanceOfComparisonRector\Fixture\Foo;

final class MyOfComparisonTest extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $expectedInstance = Foo::class;
        $expectedNamespacedInstance = \Namespaced\Foo::class;
        $this->assertTrue($something instanceof Foo);
        $this->assertTrue($something instanceof $expectedInstance);
        $this->assertTrue($something instanceof $expectedNamespacedInstance);
        $this->assertFalse($something instanceof \Namespaced\Foo);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertInstanceOfComparisonRector\Fixture;

use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertInstanceOfComparisonRector\Fixture\Foo;

final class MyOfComparisonTest extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $expectedInstance = Foo::class;
        $expectedNamespacedInstance = \Namespaced\Foo::class;
        $this->assertInstanceOf(\Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertInstanceOfComparisonRector\Fixture\Foo::class, $something);
        $this->assertInstanceOf($expectedInstance, $something);
        $this->assertInstanceOf($expectedNamespacedInstance, $something);
        $this->assertNotInstanceOf(\Namespaced\Foo::class, $something);
    }
}

?>
