<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\AddIntersectionParamToMockObjectParamRector\Fixture;

use PHPUnit\Framework\MockObject\MockObject;
use PHPUnit\Framework\TestCase;

final class SkipReassignedVariableTest extends TestCase
{
    public function test(): void
    {
        $someService = $this->createMock(\stdClass::class);
        $someService = $this->createMock(\DateTime::class);

        $this->prepareServiceMock($someService);
    }

    private function prepareServiceMock(MockObject $someService): void
    {
        $someService->expects($this->once())
            ->method('getId');
    }
}
