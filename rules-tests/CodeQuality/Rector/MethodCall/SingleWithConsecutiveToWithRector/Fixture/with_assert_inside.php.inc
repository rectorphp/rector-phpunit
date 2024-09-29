<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\SingleWithConsecutiveToWithRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\SingleWithConsecutiveToWithRector\Source\SomeMockedClass;

final class WithAssertInside extends TestCase
{
    public function test()
    {
        $someServiceMock = $this->createMock(SomeMockedClass::class);
        $someServiceMock->expects($this->exactly(3))
            ->method('prepare')
            ->withConsecutive(
                [
                    $this->equalTo('first'),
                    $this->equalTo('second')
                ]
            );
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\SingleWithConsecutiveToWithRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\SingleWithConsecutiveToWithRector\Source\SomeMockedClass;

final class WithAssertInside extends TestCase
{
    public function test()
    {
        $someServiceMock = $this->createMock(SomeMockedClass::class);
        $someServiceMock->expects($this->exactly(3))
            ->method('prepare')->with('first', 'second');
    }
}

?>
