<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\SingleWithConsecutiveToWithRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\SingleWithConsecutiveToWithRector\Source\SomeMockedClass;

final class WillReturnTheSame extends TestCase
{
    public function test()
    {
        $someServiceMock = $this->createMock(SomeMockedClass::class);
        $someServiceMock->expects($this->exactly(3))
            ->method('prepare')
            ->willReturnOnConsecutiveCalls(
                [1],
            );
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\SingleWithConsecutiveToWithRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\SingleWithConsecutiveToWithRector\Source\SomeMockedClass;

final class WillReturnTheSame extends TestCase
{
    public function test()
    {
        $someServiceMock = $this->createMock(SomeMockedClass::class);
        $someServiceMock->expects($this->exactly(3))
            ->method('prepare')
            ->willReturn(
                [1],
            );
    }
}

?>
