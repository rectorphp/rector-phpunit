<?php

namespace Rector\PHPUnit\Tests\Rector\Class_\PreferPHPUnitSelfCallRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipNonStaticAssert extends TestCase
{
    public function testMe()
    {
        $this->assertNonStatic('expected', 'actual', 'message');
    }

    public function assertNonStatic(mixed $expected, mixed $actual, string $message = '')
    {
        self::assertSame($expected, $actual, $message);
    }
}
