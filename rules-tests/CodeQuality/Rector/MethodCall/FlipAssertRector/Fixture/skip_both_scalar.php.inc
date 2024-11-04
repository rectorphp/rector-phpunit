<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\FlipAssertRector\Fixture;

final class SkipBothScalar extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $this->assertSame('some expected text', 'expected');
    }
}
