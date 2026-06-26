<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\MergeWithCallableAndWillReturnRector\Fixture;

use PHPUnit\Framework\TestCase;

final class ReturnArrayWithVariableUse extends TestCase
{
    public function test()
    {
        $initialStatements = [1, 2];

        $this->createMock('SomeClass')
            ->method('someMethod')
            ->with($this->callback(function ($arg): bool {
                return true;
            }))
            ->willReturn([$initialStatements, []]);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\MergeWithCallableAndWillReturnRector\Fixture;

use PHPUnit\Framework\TestCase;

final class ReturnArrayWithVariableUse extends TestCase
{
    public function test()
    {
        $initialStatements = [1, 2];

        $this->createMock('SomeClass')
            ->method('someMethod')
            ->willReturnCallback(function ($arg) use ($initialStatements): array {
                return [$initialStatements, []];
            });
    }
}

?>
