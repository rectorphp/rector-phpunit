<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertIssetToSpecificMethodRector\Fixture;

final class DifferentCaseMethodTest extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $this->asserttrue(isset($node['value1']), 'message');
        $this->ASSERTFALSE(isset($node['value2']));
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertIssetToSpecificMethodRector\Fixture;

final class DifferentCaseMethodTest extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $this->assertArrayHasKey('value1', $node, 'message');
        $this->assertArrayNotHasKey('value2', $node);
    }
}

?>
