<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\WithCallbackIdenticalToStandaloneAssertsRector\Fixture;

use PHPUnit\Framework\TestCase;

final class WithArrowFunction extends TestCase
{
    public function test()
    {
        $someMock = $this->getMockBuilder('AnyType')->getMock();

        $someMock->expects($this->any())
            ->method('trans')
            ->with(
                $this->callback(
                    fn ($args): bool => count($args) === 5 && $args[0] instanceof \stdClass
                )
            );
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\WithCallbackIdenticalToStandaloneAssertsRector\Fixture;

use PHPUnit\Framework\TestCase;

final class WithArrowFunction extends TestCase
{
    public function test()
    {
        $someMock = $this->getMockBuilder('AnyType')->getMock();

        $someMock->expects($this->any())
            ->method('trans')
            ->with(
                $this->callback(
                    function ($args): void {
                        $this->assertCount(5, $args);
                        $this->assertInstanceOf(\stdClass::class, $args[0]);
                        return true;
                    }
                )
            );
    }
}

?>
