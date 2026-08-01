<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\AddIntersectionParamToMockObjectParamRector\Fixture;

use PHPUnit\Framework\MockObject\MockObject;
use PHPUnit\Framework\TestCase;

final class DirectCreateMockArgTest extends TestCase
{
    public function test(): void
    {
        $this->prepareServiceMock($this->createMock(\stdClass::class));
    }

    private function prepareServiceMock(MockObject $someService): void
    {
        $someService->expects($this->once())
            ->method('getId');
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\AddIntersectionParamToMockObjectParamRector\Fixture;

use PHPUnit\Framework\MockObject\MockObject;
use PHPUnit\Framework\TestCase;

final class DirectCreateMockArgTest extends TestCase
{
    public function test(): void
    {
        $this->prepareServiceMock($this->createMock(\stdClass::class));
    }

    /**
     * @param \stdClass&\PHPUnit\Framework\MockObject\MockObject $someService
     */
    private function prepareServiceMock(MockObject $someService): void
    {
        $someService->expects($this->once())
            ->method('getId');
    }
}

?>
