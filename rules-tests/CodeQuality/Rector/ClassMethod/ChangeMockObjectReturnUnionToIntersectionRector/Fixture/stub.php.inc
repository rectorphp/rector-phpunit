<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\ChangeMockObjectReturnUnionToIntersectionRector\Fixture;

use PHPUnit\Framework\MockObject\Stub;
use PHPUnit\Framework\TestCase;

final class StubTest extends TestCase
{
    /**
     * @return Event|Stub
     */
    private function createEvent(): Stub
    {
        return $this->createStub(Event::class);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\ChangeMockObjectReturnUnionToIntersectionRector\Fixture;

use PHPUnit\Framework\MockObject\Stub;
use PHPUnit\Framework\TestCase;

final class StubTest extends TestCase
{
    /**
     * @return Event&Stub
     */
    private function createEvent(): Stub
    {
        return $this->createStub(Event::class);
    }
}

?>
