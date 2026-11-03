<?php

namespace Rector\PHPUnit\Tests\PHPUnit90\Rector\MethodCall\AssertRegExpRector\Fixture;

final class SkipUnpackedPregMatchArgs extends \PHPUnit\Framework\TestCase
{
    public function testFoo(array $args): void
    {
        $this->assertSame(1, preg_match(...$args));
        $this->assertSame(1, preg_match('/^keys=\d+/', ...$args));
    }
}
