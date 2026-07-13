<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\VoidMethodWithCallbackToWillReturnCallbackRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\VoidMethodWithCallbackToWillReturnCallbackRector\Source\SomeEntityManager;

final class SkipWillReturnCallbackThrow extends TestCase
{
    public function test($matcher): void
    {
        $this->createMock(SomeEntityManager::class)
            ->method('persist')
            ->willReturnCallback(function ($entity) use ($matcher) {
                if (1 === $matcher->numberOfInvocations()) {
                    return null;
                }

                if (2 === $matcher->numberOfInvocations()) {
                    return throw new \RuntimeException('boom');
                }
            });
    }
}
