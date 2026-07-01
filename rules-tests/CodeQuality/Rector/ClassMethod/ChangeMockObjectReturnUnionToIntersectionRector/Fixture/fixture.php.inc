<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\ChangeMockObjectReturnUnionToIntersectionRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SomeTest extends TestCase
{
    /**
     * @return Event|\PHPUnit\Framework\MockObject\MockObject
     */
    private function createEvent(): \PHPUnit\Framework\MockObject\MockObject
    {
        return $this->createMock(Event::class);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\ChangeMockObjectReturnUnionToIntersectionRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SomeTest extends TestCase
{
    /**
     * @return Event&\PHPUnit\Framework\MockObject\MockObject
     */
    private function createEvent(): \PHPUnit\Framework\MockObject\MockObject
    {
        return $this->createMock(Event::class);
    }
}

?>
