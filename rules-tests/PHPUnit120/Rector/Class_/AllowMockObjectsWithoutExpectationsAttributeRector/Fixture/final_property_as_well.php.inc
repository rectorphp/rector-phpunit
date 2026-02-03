<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\Class_\AllowMockObjectsWithoutExpectationsAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\PHPUnit120\Rector\Class_\AllowMockObjectsWithoutExpectationsAttributeRector\Source\SomeFinalClass;

final class FinalPropertyAsWell extends TestCase
{
    private \PHPUnit\Framework\MockObject\MockObject $someMock;

    protected function setUp(): void
    {
        $this->someMock = $this->createMock(SomeFinalClass::class);
        $this->someMock->method('some')->willReturn(true);
    }

    public function testOne()
    {
    }

    public function testTwo()
    {
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\Class_\AllowMockObjectsWithoutExpectationsAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\PHPUnit120\Rector\Class_\AllowMockObjectsWithoutExpectationsAttributeRector\Source\SomeFinalClass;

#[\PHPUnit\Framework\Attributes\AllowMockObjectsWithoutExpectations]
final class FinalPropertyAsWell extends TestCase
{
    private \PHPUnit\Framework\MockObject\MockObject $someMock;

    protected function setUp(): void
    {
        $this->someMock = $this->createMock(SomeFinalClass::class);
        $this->someMock->method('some')->willReturn(true);
    }

    public function testOne()
    {
    }

    public function testTwo()
    {
    }
}

?>
