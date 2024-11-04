<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\FlipAssertRector\Fixture;

final class SomeTest extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $result = '...';
        $this->assertSame($result, 'expected');
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\FlipAssertRector\Fixture;

final class SomeTest extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $result = '...';
        $this->assertSame('expected', $result);
    }
}

?>
