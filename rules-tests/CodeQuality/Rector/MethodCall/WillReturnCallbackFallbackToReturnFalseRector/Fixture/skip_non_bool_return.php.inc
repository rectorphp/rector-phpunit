<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\WillReturnCallbackFallbackToReturnFalseRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipNonBoolReturn extends TestCase
{
    public function test()
    {
        $matcher = $this->exactly(2);

        $eventMock = $this->createMock(\stdClass::class);
        $eventMock->expects($matcher)->method('run')->willReturnCallback(function (...$parameters) use ($matcher) {
            if (1 === $matcher->numberOfInvocations()) {
                return 1;
            }
            if (2 === $matcher->numberOfInvocations()) {
                return false;
            }
        });
    }
}
