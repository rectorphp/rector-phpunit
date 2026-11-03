<?php

namespace Rector\PHPUnit\Tests\PHPUnit90\Rector\MethodCall\AssertRegExpRector\Fixture;

final class SkipNonLiteralExpected extends \PHPUnit\Framework\TestCase
{
    public function testFoo(bool $expectMatch, int $expected): void
    {
        $string = 'keys=1000';

        $this->assertSame($expectMatch ? 1 : 0, preg_match('/^keys=\d+/', $string));
        $this->assertSame($expected, preg_match('/^keys=\d+/', $string));
        $this->assertSame(2, preg_match('/^keys=\d+/', $string));
    }
}
