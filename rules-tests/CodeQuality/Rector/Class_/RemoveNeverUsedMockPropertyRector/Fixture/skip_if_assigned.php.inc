<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\RemoveNeverUsedMockPropertyRector\Fixture;

use PHPUnit\Framework\MockObject\MockObject;
use PHPUnit\Framework\TestCase;

final class SkipIfAssigned extends TestCase
{
    private MockObject $mockProperty;

    protected function setUp(): void
    {
        $this->mockProperty = $this->createMock(\stdClass::class);
        $this->mockProperty->expects($this->once())
            ->method('someMethod')
            ->willReturn('someValue');

        $anotherObject = new \stdClass();
        $anotherObject->nested = $this->mockProperty;
    }
}
