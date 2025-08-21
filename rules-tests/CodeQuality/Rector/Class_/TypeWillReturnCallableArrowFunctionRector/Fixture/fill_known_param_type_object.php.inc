<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\TypeWillReturnCallableArrowFunctionRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\TypeWillReturnCallableArrowFunctionRector\Source\SomeMockedClass;

final class FillKnownParamTypeObject extends TestCase
{
    public function test($value): void
    {
        $this->createMock(SomeMockedClass::class)
            ->method('nativeObject')
            ->willReturnCallback(fn (object $object) => $value);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\TypeWillReturnCallableArrowFunctionRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\TypeWillReturnCallableArrowFunctionRector\Source\SomeMockedClass;

final class FillKnownParamTypeObject extends TestCase
{
    public function test($value): void
    {
        $this->createMock(SomeMockedClass::class)
            ->method('nativeObject')
            ->willReturnCallback(fn (object $name): object => $value);
    }
}

?>
