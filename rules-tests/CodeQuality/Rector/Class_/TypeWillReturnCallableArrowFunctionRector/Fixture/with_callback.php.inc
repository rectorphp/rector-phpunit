<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\TypeWillReturnCallableArrowFunctionRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\TypeWillReturnCallableArrowFunctionRector\Source\SomeMockedClass;

final class FillKnownParamType extends TestCase
{
    public function test($value): void
    {
        $this->createMock(SomeMockedClass::class)
            ->method('someMethod')
            ->with($this->callback(fn ($name) => $value));
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\TypeWillReturnCallableArrowFunctionRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\TypeWillReturnCallableArrowFunctionRector\Source\SomeMockedClass;

final class FillKnownParamType extends TestCase
{
    public function test($value): void
    {
        $this->createMock(SomeMockedClass::class)
            ->method('someMethod')
            ->with($this->callback(fn (string $name): int => $value));
    }
}

?>
