<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\SingleWithConsecutiveToWithRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\NarrowIdenticalWithConsecutiveRector\Source\SomeMockedClass;

final class SkipMultipleValues extends TestCase
{
    public function test()
    {
        $someServiceMock = $this->createMock(SomeMockedClass::class);
        $someServiceMock->expects($this->exactly(3))
            ->method('prepare')
            ->withConsecutive(
                [1],
                [2],
            );
    }
}
