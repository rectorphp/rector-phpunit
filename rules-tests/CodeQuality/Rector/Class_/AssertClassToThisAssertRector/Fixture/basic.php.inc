<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\AssertClassToThisAssertRector\Fixture;

use PHPUnit\Framework\Assert;
use PHPUnit\Framework\TestCase;

final class BasicTest extends TestCase
{
    public function testMe()
    {
        Assert::assertSame(1, 1);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\AssertClassToThisAssertRector\Fixture;

use PHPUnit\Framework\Assert;
use PHPUnit\Framework\TestCase;

final class BasicTest extends TestCase
{
    public function testMe()
    {
        $this->assertSame(1, 1);
    }
}

?>
