<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\FlipAssertRector\Fixture;

final class AssertSameNull extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $result = '...';
        $this->assertSame($result, null);
        $this->assertNotSame($result, false);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\FlipAssertRector\Fixture;

final class AssertSameNull extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $result = '...';
        $this->assertSame(null, $result);
        $this->assertNotSame(false, $result);
    }
}

?>
