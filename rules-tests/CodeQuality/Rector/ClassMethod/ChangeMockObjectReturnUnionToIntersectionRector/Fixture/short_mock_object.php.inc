<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\ChangeMockObjectReturnUnionToIntersectionRector\Fixture;

use PHPUnit\Framework\MockObject\MockObject;
use PHPUnit\Framework\TestCase;

final class ShortMockObjectTest extends TestCase
{
    /**
     * @return Event|MockObject
     */
    private function createEvent(): MockObject
    {
        return $this->createMock(Event::class);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\ChangeMockObjectReturnUnionToIntersectionRector\Fixture;

use PHPUnit\Framework\MockObject\MockObject;
use PHPUnit\Framework\TestCase;

final class ShortMockObjectTest extends TestCase
{
    /**
     * @return Event&MockObject
     */
    private function createEvent(): MockObject
    {
        return $this->createMock(Event::class);
    }
}

?>
