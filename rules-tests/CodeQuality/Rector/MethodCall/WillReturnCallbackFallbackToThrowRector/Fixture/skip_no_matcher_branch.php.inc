<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\WillReturnCallbackFallbackToThrowRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipNoMatcherBranch extends TestCase
{
    public function test()
    {
        $matcher = $this->exactly(1);

        $someServiceMock = $this->createMock(SomeMockedClass::class);
        $someServiceMock->expects($matcher)
            ->method('run')
            ->willReturnCallback(function () use ($matcher) {
                return 'value';
            });
    }
}
