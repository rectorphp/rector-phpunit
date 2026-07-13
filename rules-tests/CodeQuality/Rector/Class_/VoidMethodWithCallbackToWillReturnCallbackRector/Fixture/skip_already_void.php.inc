<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\VoidMethodWithCallbackToWillReturnCallbackRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\VoidMethodWithCallbackToWillReturnCallbackRector\Source\SomeEntityManager;

final class SkipAlreadyVoid extends TestCase
{
    public function test(): void
    {
        $this->createMock(SomeEntityManager::class)
            ->method('persist')
            ->willReturnCallback(function ($entity): void {
                echo $entity;
            });
    }
}
