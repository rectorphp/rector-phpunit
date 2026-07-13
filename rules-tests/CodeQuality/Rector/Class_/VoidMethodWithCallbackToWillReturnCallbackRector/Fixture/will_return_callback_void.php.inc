<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\VoidMethodWithCallbackToWillReturnCallbackRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\VoidMethodWithCallbackToWillReturnCallbackRector\Source\SomeEntityManager;

final class WillReturnCallbackVoid extends TestCase
{
    public function test($value): void
    {
        $this->createMock(SomeEntityManager::class)
            ->method('persist')
            ->willReturnCallback(function ($entity) {
                echo $entity;

                return true;
            });
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\VoidMethodWithCallbackToWillReturnCallbackRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\VoidMethodWithCallbackToWillReturnCallbackRector\Source\SomeEntityManager;

final class WillReturnCallbackVoid extends TestCase
{
    public function test($value): void
    {
        $this->createMock(SomeEntityManager::class)
            ->method('persist')
            ->willReturnCallback(function ($entity): void {
                echo $entity;
            });
    }
}

?>
