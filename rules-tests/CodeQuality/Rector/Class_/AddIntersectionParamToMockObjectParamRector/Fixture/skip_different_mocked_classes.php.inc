<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\AddIntersectionParamToMockObjectParamRector\Fixture;

use PHPUnit\Framework\MockObject\MockObject;
use PHPUnit\Framework\TestCase;

final class SkipDifferentMockedClassesTest extends TestCase
{
    public function testFirst(): void
    {
        $someService = $this->createMock(\stdClass::class);
        $this->prepareServiceMock($someService);
    }

    public function testSecond(): void
    {
        $someService = $this->createMock(\DateTime::class);
        $this->prepareServiceMock($someService);
    }

    private function prepareServiceMock(MockObject $someService): void
    {
        $someService->expects($this->once())
            ->method('getId');
    }
}
