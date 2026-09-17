<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\WillReturnCallbackFallbackToReturnFalseRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipNoReturn extends TestCase
{
    public function test()
    {
        $matcher = $this->exactly(1);

        $eventMock = $this->createMock(\stdClass::class);
        $eventMock->expects($matcher)->method('run')->willReturnCallback(function (...$parameters) use ($matcher) {
            $this->assertSame(['emails'], $parameters[0]);
        });
    }
}
