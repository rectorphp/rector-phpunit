<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\BareCreateMockAssignToDirectUseRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipUsedAsMock extends TestCase
{
    public function test()
    {
        $someMock = $this->createMock(\Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\BareCreateMockAssignToDirectUseRector\Source\AnotherClass::class);

        $someMock->expects($this->atLeastOnce())
            ->method('some');

        $this->useMock($someMock);
    }

    private function useMock($someMock)
    {
    }
}
