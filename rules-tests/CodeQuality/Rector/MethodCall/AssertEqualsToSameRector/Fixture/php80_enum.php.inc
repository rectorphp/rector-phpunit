<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertEqualsToSameRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertEqualsToSameRector\Source\SimpleEnum;

final class Php80Enum extends TestCase
{
    public function test(string $result)
    {
        $this->assertEquals(SimpleEnum::LEFT, $result);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertEqualsToSameRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertEqualsToSameRector\Source\SimpleEnum;

final class Php80Enum extends TestCase
{
    public function test(string $result)
    {
        $this->assertSame(SimpleEnum::LEFT, $result);
    }
}

?>
