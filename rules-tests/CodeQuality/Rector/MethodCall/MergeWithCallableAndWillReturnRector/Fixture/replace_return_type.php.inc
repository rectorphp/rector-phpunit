<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\MergeWithCallableAndWillReturnRector\Fixture;

use PHPUnit\Framework\TestCase;

final class ReplaceReturnType extends TestCase
{
    public function test()
    {
        $this->createMock('SomeClass')
            ->method('someMethod')
            ->with($this->callback(function ($arg): bool {
                return true;
            }))
            ->willReturn('someValue');
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\MergeWithCallableAndWillReturnRector\Fixture;

use PHPUnit\Framework\TestCase;

final class ReplaceReturnType extends TestCase
{
    public function test()
    {
        $this->createMock('SomeClass')
            ->method('someMethod')
            ->willReturnCallback(function ($arg): string {
                return 'someValue';
            });
    }
}

?>
