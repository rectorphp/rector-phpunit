<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\MethodCall\AssertPropertyExistsRector\Fixture;

final class MyTest2 extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $response = new \Namespaced\Response();
        $this->assertObjectNotHasAttribute('property', $response);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\MethodCall\AssertPropertyExistsRector\Fixture;

final class MyTest2 extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $response = new \Namespaced\Response();
        $this->assertFalse(property_exists($response, 'property'));
    }
}

?>
