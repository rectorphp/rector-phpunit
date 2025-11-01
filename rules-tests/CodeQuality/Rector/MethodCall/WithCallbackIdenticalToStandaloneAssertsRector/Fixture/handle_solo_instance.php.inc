<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\WithCallbackIdenticalToStandaloneAssertsRector\Fixture;

use PHPUnit\Framework\TestCase;

final class HandleSoloInstance extends TestCase
{
    public function test()
    {
        $someMock = $this->createMock('AnyType')
            ->expects($this->any())
            ->method('trans')
            ->with(
                $this->callback(
                    fn ($arg): bool => $arg instanceof \stdClass
                )
            );
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\WithCallbackIdenticalToStandaloneAssertsRector\Fixture;

use PHPUnit\Framework\TestCase;

final class HandleSoloInstance extends TestCase
{
    public function test()
    {
        $someMock = $this->createMock('AnyType')
            ->expects($this->any())
            ->method('trans')
            ->with(
                $this->callback(
                    function ($arg): bool {
                        $this->assertInstanceOf(\stdClass::class, $arg);
                        return true;
                    }
                )
            );
    }
}

?>
