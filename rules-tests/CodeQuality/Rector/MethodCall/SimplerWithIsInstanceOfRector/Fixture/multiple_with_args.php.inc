<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\SimplerWithIsInstanceOfRector\Fixture;

use PHPUnit\Framework\TestCase;

final class MultipleWithArgs extends TestCase
{
    public function test()
    {
        $someMock = $this->getMockBuilder('AnyType')->getMock();

        $someMock->expects($this->any())
            ->method('dispatch')
            ->with($this->callback(function ($event): bool {
                $this->assertInstanceOf(\stdClass::class, $event);
                return true;
            }), $this->callback(function ($name): bool {
                $this->assertInstanceOf(\Stringable::class, $name);
                return true;
            }));
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\SimplerWithIsInstanceOfRector\Fixture;

use PHPUnit\Framework\TestCase;

final class MultipleWithArgs extends TestCase
{
    public function test()
    {
        $someMock = $this->getMockBuilder('AnyType')->getMock();

        $someMock->expects($this->any())
            ->method('dispatch')
            ->with($this->isInstanceOf(\stdClass::class), $this->isInstanceOf(\Stringable::class));
    }
}

?>
