<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\BareCreateMockAssignToDirectUseRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipMultipleUsesAsArg extends TestCase
{
    public function test()
    {
        $someMock = $this->createMock(\Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\BareCreateMockAssignToDirectUseRector\Source\AnotherClass::class);

        // behaviour can already changed on first use
        $this->useMock($someMock);
        $this->useMockAgain($someMock);
    }

    private function useMock($someMock)
    {
        $someMock->method('someMethod');
    }

    private function useMockAgain($someMock)
    {
    }
}
