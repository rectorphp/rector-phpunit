<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\FlipAssertRector\Fixture;

final class NotSame extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $result = '...';
        $this->assertNotSame($result, 'expected');
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\FlipAssertRector\Fixture;

final class NotSame extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $result = '...';
        $this->assertNotSame('expected', $result);
    }
}

?>
