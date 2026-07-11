<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\RemoveReturnFromVoidMethodMockCallbackRector\Fixture;

use PHPUnit\Framework\MockObject\MockObject;
use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\RemoveReturnFromVoidMethodMockCallbackRector\Source\SomeEntityManager;

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
            ->with($this->callback(function ($entity): bool {
                $this->assertInstanceOf(\stdClass::class, $entity);

                return true;
            }));
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\RemoveReturnFromVoidMethodMockCallbackRector\Fixture;

use PHPUnit\Framework\MockObject\MockObject;
use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\RemoveReturnFromVoidMethodMockCallbackRector\Source\SomeEntityManager;

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
            ->with($this->callback(function ($entity): void {
                $this->assertInstanceOf(\stdClass::class, $entity);
            }));
    }
}

?>
