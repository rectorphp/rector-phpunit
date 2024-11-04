<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertEqualsToSameRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertEqualsToSameRector\Source\SimpleConstantList;
use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertEqualsToSameRector\Source\SimpleEnum;

final class ClassConstant extends TestCase
{
    public function test($result)
    {
        $this->assertEquals(SimpleConstantList::BOTTOM, $result);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertEqualsToSameRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertEqualsToSameRector\Source\SimpleConstantList;
use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertEqualsToSameRector\Source\SimpleEnum;

final class ClassConstant extends TestCase
{
    public function test($result)
    {
        $this->assertSame(SimpleConstantList::BOTTOM, $result);
    }
}

?>
