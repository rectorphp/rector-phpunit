<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertIssetToSpecificMethodRector\Fixture;

final class MyIssetTest extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $this->assertTrue(isset($node['value1']), 'message');
        $this->assertFalse(isset($node['value2']));
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertIssetToSpecificMethodRector\Fixture;

final class MyIssetTest extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $this->assertArrayHasKey('value1', $node, 'message');
        $this->assertArrayNotHasKey('value2', $node);
    }
}

?>
