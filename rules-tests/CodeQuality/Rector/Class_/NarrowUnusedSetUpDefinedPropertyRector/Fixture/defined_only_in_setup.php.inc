<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\NarrowUnusedSetUpDefinedPropertyRector\Fixture;

use PHPUnit\Framework\MockObject\MockObject;
use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\NarrowUnusedSetUpDefinedPropertyRector\Source\SomeType;

final class DefinedOnlyInSetup extends TestCase
{
    private MockObject $someMock;

    private MockObject $anotherMock;

    protected function setUp(): void
    {
        $this->someMock = $this->createMock(SomeType::class);
        $this->anotherMock = $this->createMock(SomeType::class);
    }

    public function test()
    {
        $this->anotherMock->expects($this->once());
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\NarrowUnusedSetUpDefinedPropertyRector\Fixture;

use PHPUnit\Framework\MockObject\MockObject;
use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\NarrowUnusedSetUpDefinedPropertyRector\Source\SomeType;

final class DefinedOnlyInSetup extends TestCase
{
    private MockObject $anotherMock;

    protected function setUp(): void
    {
        $someMock = $this->createMock(SomeType::class);
        $this->anotherMock = $this->createMock(SomeType::class);
    }

    public function test()
    {
        $this->anotherMock->expects($this->once());
    }
}

?>
