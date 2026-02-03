<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\Class_\AllowMockObjectsWithoutExpectationsAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AddToSetupWhenNoExpects extends TestCase
{
    private \PHPUnit\Framework\MockObject\MockObject $someMock;

    protected function setUp(): void
    {
        $this->someMock = $this->createMock(\stdClass::class);
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

#[\PHPUnit\Framework\Attributes\AllowMockObjectsWithoutExpectations]
final class AddToSetupWhenNoExpects extends TestCase
{
    private \PHPUnit\Framework\MockObject\MockObject $someMock;

    protected function setUp(): void
    {
        $this->someMock = $this->createMock(\stdClass::class);
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
