<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\RemoveNeverUsedMockPropertyRector\Fixture;

use PHPUnit\Framework\MockObject\MockObject;
use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\RemoveNeverUsedMockPropertyRector\Source\UsesMockPropertyTrait;

final class SkipIfUsedInTrait extends TestCase
{
    use UsesMockPropertyTrait;

    private MockObject $mockProperty;

    protected function setUp(): void
    {
        $this->mockProperty = $this->createMock(\stdClass::class);
        $this->mockProperty->expects($this->once())
            ->method('someMethod')
            ->willReturn('someValue');
    }
}
