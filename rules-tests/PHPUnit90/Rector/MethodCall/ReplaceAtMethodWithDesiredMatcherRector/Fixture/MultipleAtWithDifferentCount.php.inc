<?php

namespace Rector\PHPUnit\Tests\PHPUnit90\Rector\MethodCall\ReplaceAtMethodWithDesiredMatcherRector\Fixture;

use PHPUnit\Framework\TestCase;

final class MultipleAtWithDifferentCount extends TestCase
{
    public function test()
    {
        $mock->expects($this->at(0))
             ->method('foo')
             ->willReturn('1');

        $mock->expects($this->at(1))
             ->method('foo')
             ->willReturn('1');

        $mock->expects($this->at(2))
             ->method('foo')
             ->willReturn('1');
        $mock->expects($this->at(3))
             ->method('foo')
             ->willReturn('1');
    }
}
?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit90\Rector\MethodCall\ReplaceAtMethodWithDesiredMatcherRector\Fixture;

use PHPUnit\Framework\TestCase;

final class MultipleAtWithDifferentCount extends TestCase
{
    public function test()
    {
        $mock->expects($this->never())
             ->method('foo')
             ->willReturn('1');

        $mock->expects($this->once())
             ->method('foo')
             ->willReturn('1');

        $mock->expects($this->exactly(2))
             ->method('foo')
             ->willReturn('1');
        $mock->expects($this->exactly(3))
             ->method('foo')
             ->willReturn('1');
    }
}
?>
