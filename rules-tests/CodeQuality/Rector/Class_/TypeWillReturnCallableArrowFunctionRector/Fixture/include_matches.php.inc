<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\TypeWillReturnCallableArrowFunctionRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\TypeWillReturnCallableArrowFunctionRector\Source\SomeMockedClass;

final class IncludeMatcher extends TestCase
{
    public function test($value): void
    {
        $this->createMock(SomeMockedClass::class)
            ->expects($this->any())
            ->method('someMethod')
            ->willReturnCallback(fn ($name) => $value);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\TypeWillReturnCallableArrowFunctionRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\TypeWillReturnCallableArrowFunctionRector\Source\SomeMockedClass;

final class IncludeMatcher extends TestCase
{
    public function test($value): void
    {
        $this->createMock(SomeMockedClass::class)
            ->expects($this->any())
            ->method('someMethod')
            ->willReturnCallback(fn (string $name): int => $value);
    }
}

?>
