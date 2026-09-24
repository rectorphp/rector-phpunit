<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\FlipAssertRector\Fixture;

final class SkipNamedArgs extends \PHPUnit\Framework\TestCase
{
    public function test($result)
    {
        $this->assertSame(expected: $result->ids(), actual: [1, 2]);
    }
}

?>
