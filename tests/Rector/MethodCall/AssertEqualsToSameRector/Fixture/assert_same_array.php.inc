<?php

namespace Rector\PHPUnit\Tests\Rector\MethodCall\AssertEqualsToSameRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AssertSameArray extends TestCase
{
    public function test($result)
    {
        $expected = [1 => 2];
        $this->assertEquals($expected, $result);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\Rector\MethodCall\AssertEqualsToSameRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AssertSameArray extends TestCase
{
    public function test($result)
    {
        $expected = [1 => 2];
        $this->assertSame($expected, $result);
    }
}

?>
