<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\FlipAssertRector\Fixture;

final class SkipEnumValueFirst extends \PHPUnit\Framework\TestCase
{
    public function test($result, $status, $x)
    {
        $this->assertSame(Status::Active->value, [$x]);
        $this->assertSame($result->status, $status->value);
    }
}

?>
