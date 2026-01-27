<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\Class_\AllowMockObjectsWithoutExpectationsAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SomeClass extends TestCase
{
    private \PHPUnit\Framework\MockObject\MockObject $someMock;

    protected function setUp(): void
    {
        $this->someMock = $this->createMock(\stdClass::class);
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
final class SomeClass extends TestCase
{
    private \PHPUnit\Framework\MockObject\MockObject $someMock;

    protected function setUp(): void
    {
        $this->someMock = $this->createMock(\stdClass::class);
    }

    public function testOne()
    {
    }

    public function testTwo()
    {

    }
}

?>
