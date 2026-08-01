<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\AddIntersectionParamToMockObjectParamRector\Fixture;

use PHPUnit\Framework\MockObject\MockObject;
use PHPUnit\Framework\TestCase;

final class SkipExistingParamDocTest extends TestCase
{
    public function test(): void
    {
        $someService = $this->createMock(\stdClass::class);
        $this->prepareServiceMock($someService);
    }

    /**
     * @param MockObject $someService
     */
    private function prepareServiceMock(MockObject $someService): void
    {
        $someService->expects($this->once())
            ->method('getId');
    }
}
