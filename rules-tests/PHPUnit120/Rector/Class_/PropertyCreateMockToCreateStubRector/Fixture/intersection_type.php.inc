<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\Class_\PropertyCreateMockToCreateStubRector\Fixture;

use PHPUnit\Framework\TestCase;

final class IntersectionTypeTest extends TestCase
{
    private \PHPUnit\Framework\MockObject\MockObject&\stdClass $someMock;

    protected function setUp(): void
    {
        $this->someMock = $this->createMock(\stdClass::class);
    }

    public function testThis()
    {
        $this->assertSame('...', $this->someMock);
    }

    public function testThat()
    {
        $this->assertSame('...', $this->someMock);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\Class_\PropertyCreateMockToCreateStubRector\Fixture;

use PHPUnit\Framework\TestCase;

final class IntersectionTypeTest extends TestCase
{
    private \PHPUnit\Framework\MockObject\Stub&\stdClass $someMock;

    protected function setUp(): void
    {
        $this->someMock = $this->createStub(\stdClass::class);
    }

    public function testThis()
    {
        $this->assertSame('...', $this->someMock);
    }

    public function testThat()
    {
        $this->assertSame('...', $this->someMock);
    }
}

?>
