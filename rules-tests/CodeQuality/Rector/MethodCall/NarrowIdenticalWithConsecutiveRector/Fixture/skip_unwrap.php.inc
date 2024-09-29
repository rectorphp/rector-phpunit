<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\NarrowIdenticalWithConsecutiveRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\NarrowIdenticalWithConsecutiveRector\Source\SomeMockedClass;

final class SkipUnwrap extends TestCase
{
    public function test()
    {
        $items = [1, 2, 3];

        $someServiceMock = $this->createMock(SomeMockedClass::class);
        $someServiceMock->expects($this->exactly(3))
            ->method('prepare')
            ->withConsecutive(...$items);
    }
}
