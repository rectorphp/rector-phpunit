<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\MergeWithCallableAndWillReturnRector\Fixture;

use PHPUnit\Framework\TestCase;

final class ReturnVariableUse extends TestCase
{
    public function test()
    {
        $anotherValue = 1000;

        $this->createMock('SomeClass')
            ->method('someMethod')
            ->with($this->callback(function ($arg): bool {
                return true;
            }))
            ->willReturn($anotherValue);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\MergeWithCallableAndWillReturnRector\Fixture;

use PHPUnit\Framework\TestCase;

final class ReturnVariableUse extends TestCase
{
    public function test()
    {
        $anotherValue = 1000;

        $this->createMock('SomeClass')
            ->method('someMethod')
            ->willReturnCallback(function ($arg) use ($anotherValue): int {
                return $anotherValue;
            });
    }
}

?>
