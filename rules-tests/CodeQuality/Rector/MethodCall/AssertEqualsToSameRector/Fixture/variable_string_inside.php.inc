<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertEqualsToSameRector\Fixture;

use PHPUnit\Framework\TestCase;

final class VariableStringInside extends TestCase
{
    public function test($value)
    {
        $result = '...';
        $this->assertEquals("Some $value", $result);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertEqualsToSameRector\Fixture;

use PHPUnit\Framework\TestCase;

final class VariableStringInside extends TestCase
{
    public function test($value)
    {
        $result = '...';
        $this->assertSame("Some $value", $result);
    }
}

?>
