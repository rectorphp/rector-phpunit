<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertInstanceOfComparisonRector\Fixture;

use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertInstanceOfComparisonRector\Fixture\Foo;

final class MyOfComparissonTest extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $this->assertTrue($something instanceof Foo);
        $this->assertFalse($something instanceof \Namespaced\Foo);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertInstanceOfComparisonRector\Fixture;

use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertInstanceOfComparisonRector\Fixture\Foo;

final class MyOfComparissonTest extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $this->assertInstanceOf(\Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertInstanceOfComparisonRector\Fixture\Foo::class, $something);
        $this->assertNotInstanceOf(\Namespaced\Foo::class, $something);
    }
}

?>
