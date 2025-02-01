<?php

namespace Rector\PHPUnit\Tests\PHPUnit90\Rector\MethodCall\ReplaceAtMethodWithDesiredMatcherRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AtWithTwoOrMoreCount extends TestCase
{
    public function test()
    {
        $mock->expects($this->at(2))
             ->method('foo')
             ->willReturn('1');
    }
}
?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit90\Rector\MethodCall\ReplaceAtMethodWithDesiredMatcherRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AtWithTwoOrMoreCount extends TestCase
{
    public function test()
    {
        $mock->expects($this->exactly(2))
             ->method('foo')
             ->willReturn('1');
    }
}
?>
