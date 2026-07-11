<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\RemoveReturnFromVoidMethodMockCallbackRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\RemoveReturnFromVoidMethodMockCallbackRector\Source\SomeEntityManager;

final class SkipNonVoidMethod extends TestCase
{
    public function test(): void
    {
        $this->createMock(SomeEntityManager::class)
            ->method('count')
            ->willReturnCallback(function ($name) {
                return 100;
            });
    }
}
