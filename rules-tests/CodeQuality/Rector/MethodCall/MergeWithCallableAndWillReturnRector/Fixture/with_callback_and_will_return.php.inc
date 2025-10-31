<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\MergeWithCallableAndWillReturnRector\Fixture;

use PHPUnit\Framework\TestCase;

final class WithCallbackAndWillReturn extends TestCase
{
    public function test()
    {
        $this->createMock('SomeClass')
            ->method('someMethod')
            ->with($this->callback(function ($arg) {
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

final class WithCallbackAndWillReturn extends TestCase
{
    public function test()
    {
        $this->createMock('SomeClass')
            ->method('someMethod')
            ->willReturnCallback(function ($arg) {
                return 'someValue';
            });
    }
}

?>
