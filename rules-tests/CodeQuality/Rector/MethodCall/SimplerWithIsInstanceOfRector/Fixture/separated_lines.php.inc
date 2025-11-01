<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\SimplerWithIsInstanceOfRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SeparatedLines extends TestCase
{
    public function test()
    {
        $someMock = $this->getMockBuilder('AnyType')->getMock();

        $someMock->expects($this->any())
            ->method('trans')
            ->with($this->callback(function ($args): bool {
                $this->assertInstanceOf(\stdClass::class, $args);
                return true;
            }));
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\SimplerWithIsInstanceOfRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SeparatedLines extends TestCase
{
    public function test()
    {
        $someMock = $this->getMockBuilder('AnyType')->getMock();

        $someMock->expects($this->any())
            ->method('trans')
            ->with($this->isInstanceOf(\stdClass::class));
    }
}

?>
