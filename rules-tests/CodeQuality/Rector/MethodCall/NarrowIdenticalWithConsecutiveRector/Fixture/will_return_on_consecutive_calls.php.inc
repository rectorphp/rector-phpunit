<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\NarrowIdenticalWithConsecutiveRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\NarrowIdenticalWithConsecutiveRector\Source\SomeMockedClass;

final class RepeatedSame extends TestCase
{
    public function test()
    {
        $someServiceMock = $this->createMock(SomeMockedClass::class);
        $someServiceMock->expects($this->exactly(3))
            ->method('prepare')
            ->willReturnOnConsecutiveCalls(
                [4, 5],
                [4, 5],
                [4, 5],
            );
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\NarrowIdenticalWithConsecutiveRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\NarrowIdenticalWithConsecutiveRector\Source\SomeMockedClass;

final class RepeatedSame extends TestCase
{
    public function test()
    {
        $someServiceMock = $this->createMock(SomeMockedClass::class);
        $someServiceMock->expects($this->exactly(3))
            ->method('prepare')->willReturn([4, 5]);
    }
}

?>
