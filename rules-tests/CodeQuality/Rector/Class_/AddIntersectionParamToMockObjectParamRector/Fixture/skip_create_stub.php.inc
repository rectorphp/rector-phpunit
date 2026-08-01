<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\AddIntersectionParamToMockObjectParamRector\Fixture;

use PHPUnit\Framework\MockObject\MockObject;
use PHPUnit\Framework\TestCase;

final class SkipCreateStubTest extends TestCase
{
    public function test(): void
    {
        $someService = $this->createStub(\stdClass::class);
        $this->prepareServiceMock($someService);
    }

    private function prepareServiceMock(MockObject $someService): void
    {
        $someService->expects($this->once())
            ->method('getId');
    }
}
