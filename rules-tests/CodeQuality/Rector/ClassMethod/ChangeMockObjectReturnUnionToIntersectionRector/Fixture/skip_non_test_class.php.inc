<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\ChangeMockObjectReturnUnionToIntersectionRector\Fixture;

final class SkipNonTestClass
{
    /**
     * @return Event|\PHPUnit\Framework\MockObject\MockObject
     */
    private function createEvent()
    {
        return $this->createMock(Event::class);
    }
}
