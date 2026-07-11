<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\WillReturnCallbackFallbackToThrowRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipFallbackReturn extends TestCase
{
    public function test()
    {
        $matcher = $this->exactly(2);

        $someServiceMock = $this->createMock(SomeMockedClass::class);
        $someServiceMock->expects($matcher)
            ->method('run')
            ->willReturnCallback(function () use ($matcher) {
                if ($matcher->numberOfInvocations() === 1) {
                    return 'first';
                }

                if ($matcher->numberOfInvocations() === 2) {
                    return 'second';
                }

                return 'third';
            });
    }
}
