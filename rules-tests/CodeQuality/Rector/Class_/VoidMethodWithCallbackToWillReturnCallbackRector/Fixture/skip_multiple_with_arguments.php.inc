<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\VoidMethodWithCallbackToWillReturnCallbackRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\VoidMethodWithCallbackToWillReturnCallbackRector\Source\SomeEntityManager;

final class SkipMultipleWithArguments extends TestCase
{
    public function test(): void
    {
        $this->createMock(SomeEntityManager::class)
            ->method('persist')
            ->with(
                $this->callback(function ($entity): bool {
                    $this->assertInstanceOf(\stdClass::class, $entity);

                    return true;
                }),
                false
            );
    }
}
