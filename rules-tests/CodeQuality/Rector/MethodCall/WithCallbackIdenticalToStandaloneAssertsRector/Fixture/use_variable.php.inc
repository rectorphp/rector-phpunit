<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\WithCallbackIdenticalToStandaloneAssertsRector\Fixture;

use PHPUnit\Framework\TestCase;

final class UseVariable extends TestCase
{
    public function test()
    {
        $expectedValue = 100;
        $someMock = $this->getMockBuilder('AnyType')->getMock();

        $someMock->expects($this->any())
            ->method('trans')
            ->with(
                $this->callback(fn ($args): bool => count($args) === 5 && $args[0] === $expectedValue)
            );
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\WithCallbackIdenticalToStandaloneAssertsRector\Fixture;

use PHPUnit\Framework\TestCase;

final class UseVariable extends TestCase
{
    public function test()
    {
        $expectedValue = 100;
        $someMock = $this->getMockBuilder('AnyType')->getMock();

        $someMock->expects($this->any())
            ->method('trans')
            ->with(
                $this->callback(function ($args) use ($expectedValue): void {
                    $this->assertCount(5, $args);
                    $this->assertSame($expectedValue, $args[0]);
                    return true;
                })
            );
    }
}

?>
