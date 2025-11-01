<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\WithCallbackIdenticalToStandaloneAssertsRector\Fixture;

use PHPUnit\Framework\TestCase;

final class ArrowWithClassVariable extends TestCase
{
    public function test($type)
    {
        $this->createMock('SomeType')
            ->method('someMethod')
            ->with($this->callback(
                fn ($item): bool => $item instanceof $type &&
                    $item->getName() === 'name'
                ));
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\WithCallbackIdenticalToStandaloneAssertsRector\Fixture;

use PHPUnit\Framework\TestCase;

final class ArrowWithClassVariable extends TestCase
{
    public function test($type)
    {
        $this->createMock('SomeType')
            ->method('someMethod')
            ->with($this->callback(
                function ($item) use ($type): bool {
                    $this->assertInstanceOf($type, $item);
                    $this->assertSame('name', $item->getName());
                    return true;
                }
                ));
    }
}

?>
