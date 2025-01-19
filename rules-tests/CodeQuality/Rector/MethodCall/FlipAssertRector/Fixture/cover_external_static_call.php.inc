<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\FlipAssertRector\Fixture;

use PHPUnit\Framework\Assert;

final class CovertExternalStaticCall
{
    public function test()
    {
        $result = '...';
        Assert::assertStringContainsString($result, 'expected');
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\FlipAssertRector\Fixture;

use PHPUnit\Framework\Assert;

final class CovertExternalStaticCall
{
    public function test()
    {
        $result = '...';
        Assert::assertStringContainsString('expected', $result);
    }
}

?>
