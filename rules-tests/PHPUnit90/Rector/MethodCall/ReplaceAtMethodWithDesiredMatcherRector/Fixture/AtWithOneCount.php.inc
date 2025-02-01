<?php

namespace Rector\PHPUnit\Tests\PHPUnit90\Rector\MethodCall\ReplaceAtMethodWithDesiredMatcherRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AtWithOneCountTest extends TestCase
{
    public function test()
    {
        $mock->expects($this->at(1))
             ->method('foo')
             ->willReturn('1');
    }
}
?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit90\Rector\MethodCall\ReplaceAtMethodWithDesiredMatcherRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AtWithOneCountTest extends TestCase
{
    public function test()
    {
        $mock->expects($this->once())
             ->method('foo')
             ->willReturn('1');
    }
}
?>
