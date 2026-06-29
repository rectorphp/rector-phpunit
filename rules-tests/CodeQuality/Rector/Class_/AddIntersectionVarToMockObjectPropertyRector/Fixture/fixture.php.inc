<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\AddIntersectionVarToMockObjectPropertyRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SomeTest extends TestCase
{
    private \PHPUnit\Framework\MockObject\MockObject $someServiceMock;

    protected function setUp(): void
    {
        $this->someServiceMock = $this->createMock(\stdClass::class);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\AddIntersectionVarToMockObjectPropertyRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SomeTest extends TestCase
{
    /**
     * @var \PHPUnit\Framework\MockObject\MockObject&\stdClass
     */
    private \PHPUnit\Framework\MockObject\MockObject $someServiceMock;

    protected function setUp(): void
    {
        $this->someServiceMock = $this->createMock(\stdClass::class);
    }
}

?>
