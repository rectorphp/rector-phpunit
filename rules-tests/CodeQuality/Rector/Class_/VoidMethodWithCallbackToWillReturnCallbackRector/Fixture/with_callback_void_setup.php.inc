<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\VoidMethodWithCallbackToWillReturnCallbackRector\Fixture;

use PHPUnit\Framework\MockObject\MockObject;
use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\VoidMethodWithCallbackToWillReturnCallbackRector\Source\SomeEntityManager;

final class WithCallbackVoidSetup extends TestCase
{
    private MockObject $entityManager;

    protected function setUp(): void
    {
        $this->entityManager = $this->createMock(SomeEntityManager::class);
    }

    public function test(): void
    {
        $this->entityManager
            ->method('persist')
            ->with($this->callback(function ($entity) {
                $this->assertInstanceOf(\stdClass::class, $entity);

                return true;
            }));
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\VoidMethodWithCallbackToWillReturnCallbackRector\Fixture;

use PHPUnit\Framework\MockObject\MockObject;
use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\VoidMethodWithCallbackToWillReturnCallbackRector\Source\SomeEntityManager;

final class WithCallbackVoidSetup extends TestCase
{
    private MockObject $entityManager;

    protected function setUp(): void
    {
        $this->entityManager = $this->createMock(SomeEntityManager::class);
    }

    public function test(): void
    {
        $this->entityManager
            ->method('persist')
            ->willReturnCallback(function ($entity) {
                $this->assertInstanceOf(\stdClass::class, $entity);
            });
    }
}

?>
