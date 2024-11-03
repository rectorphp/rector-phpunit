<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\NarrowUnusedSetUpDefinedPropertyRector\Fixture;

use PHPUnit\Framework\MockObject\MockObject;
use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\NarrowUnusedSetUpDefinedPropertyRector\Source\SomeType;

final class AnyTypeDefinedOnlyInSetup extends TestCase
{
    private $startValue;

    private MockObject $anotherMock;

    protected function setUp(): void
    {
        $this->startValue = 100;

        $this->anotherMock = $this->createMock(SomeType::class)
            ->expects($this->once())->willReturn($this->startValue);
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

final class AnyTypeDefinedOnlyInSetup extends TestCase
{
    private MockObject $anotherMock;

    protected function setUp(): void
    {
        $startValue = 100;

        $this->anotherMock = $this->createMock(SomeType::class)
            ->expects($this->once())->willReturn($startValue);
    }

    public function test()
    {
        $this->anotherMock->expects($this->once());
    }
}

?>
