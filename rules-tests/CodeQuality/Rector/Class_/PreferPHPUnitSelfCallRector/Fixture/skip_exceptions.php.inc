<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\PreferPHPUnitSelfCallRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipExceptions extends TestCase
{
    public function testMe()
    {
        // this calls should be preserved with $this, because methods are not static
        $this->expectException(\RuntimeException::class);
        $this->expectExceptionMessage('foo');
        $this->expectExceptionCode(123);
    }
}
