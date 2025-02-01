<?php

namespace Rector\PHPUnit\Tests\PHPUnit90\Rector\MethodCall\ReplaceAtMethodWithDesiredMatcherRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AtWithZeroCountTest extends TestCase
{
    public function test()
    {
        $mock->expects($this->at(0))
             ->method('foo')
             ->willReturn('1');
    }
}
?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit90\Rector\MethodCall\ReplaceAtMethodWithDesiredMatcherRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AtWithZeroCountTest extends TestCase
{
    public function test()
    {
        $mock->expects($this->never())
             ->method('foo')
             ->willReturn('1');
    }
}
?>
