<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\SuffixMockObjectPropertyRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SomeFileTest extends TestCase
{
    private \PHPUnit\Framework\MockObject\MockObject $someProperty;

    protected function setUp(): void
    {
        $this->someProperty = $this->createMock(\stdClass::class);
    }

    public function testMocks(): void
    {
        $this->someProperty->expects($this->once())->method('someMethod')->willReturn('someValue');
    }
}

?>
-----
<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\SuffixMockObjectPropertyRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SomeFileTest extends TestCase
{
    private \PHPUnit\Framework\MockObject\MockObject $somePropertyMock;

    protected function setUp(): void
    {
        $this->somePropertyMock = $this->createMock(\stdClass::class);
    }

    public function testMocks(): void
    {
        $this->somePropertyMock->expects($this->once())->method('someMethod')->willReturn('someValue');
    }
}

?>
