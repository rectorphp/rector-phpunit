<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\RemoveNeverUsedMockPropertyRector\Fixture;

use PHPUnit\Framework\MockObject\MockObject;
use PHPUnit\Framework\TestCase;
use Symfony\Component\DependencyInjection\Argument\RewindableGenerator;

final class SkipUsedInYield extends TestCase
{
    private MockObject $mockProperty;

    protected function setUp(): void
    {
        $this->mockProperty = $this->createMock(\stdClass::class);
        $this->mockProperty->expects($this->once())
            ->method('someMethod')
            ->willReturn('someValue');

        $someValue = new RewindableGenerator(fn () => yield from [$this->mockProperty], 1);
    }
}
