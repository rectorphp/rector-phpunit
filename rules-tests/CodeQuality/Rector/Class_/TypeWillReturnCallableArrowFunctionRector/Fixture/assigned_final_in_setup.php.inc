<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\TypeWillReturnCallableArrowFunctionRector\Fixture;

use Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\TypeWillReturnCallableArrowFunctionRector\Source\SomeFinalMockedClass;
use PHPUnit\Framework\MockObject\MockObject;
use PHPUnit\Framework\TestCase;

final class AssignedFinalInSetup extends TestCase
{
    private MockObject $someFinalMockedClass;

    protected function setUp(): void
    {
        $this->someFinalMockedClass = $this->createMock(SomeFinalMockedClass::class);
    }

    public function test($value): void
    {
        $this->someFinalMockedClass
            ->method('anotherMethod')
            ->willReturnCallback(fn ($age) => $value);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\TypeWillReturnCallableArrowFunctionRector\Fixture;

use Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\TypeWillReturnCallableArrowFunctionRector\Source\SomeFinalMockedClass;
use PHPUnit\Framework\MockObject\MockObject;
use PHPUnit\Framework\TestCase;

final class AssignedFinalInSetup extends TestCase
{
    private MockObject $someFinalMockedClass;

    protected function setUp(): void
    {
        $this->someFinalMockedClass = $this->createMock(SomeFinalMockedClass::class);
    }

    public function test($value): void
    {
        $this->someFinalMockedClass
            ->method('anotherMethod')
            ->willReturnCallback(fn (int $age): float => $value);
    }
}

?>
