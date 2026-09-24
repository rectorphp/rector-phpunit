<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\FlipAssertRector\Fixture;

final class EnumValue extends \PHPUnit\Framework\TestCase
{
    public function test($result)
    {
        $this->assertSame($result->status, Status::Active->value);
        $this->assertSame($result->getStatusName(), Status::Active->name);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\FlipAssertRector\Fixture;

final class EnumValue extends \PHPUnit\Framework\TestCase
{
    public function test($result)
    {
        $this->assertSame(Status::Active->value, $result->status);
        $this->assertSame(Status::Active->name, $result->getStatusName());
    }
}

?>
