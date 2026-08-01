<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\AddIntersectionParamToMockObjectParamRector\Fixture;

use PHPUnit\Framework\MockObject\MockObject;
use PHPUnit\Framework\TestCase;

final class SkipPublicMethodTest extends TestCase
{
    public function test(): void
    {
        $someService = $this->createMock(\stdClass::class);
        $this->prepareServiceMock($someService);
    }

    public function prepareServiceMock(MockObject $someService): void
    {
        $someService->expects($this->once())
            ->method('getId');
    }
}
