<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\UseSpecificWillMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class WillWithStatic extends TestCase
{
    public function test()
    {
        $translator = $this->createMock('SomeObject');
        $translator->expects($this->any())
            ->method('someMethod')
            ->will(self::throwException(new \RuntimeException()));
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\UseSpecificWillMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class WillWithStatic extends TestCase
{
    public function test()
    {
        $translator = $this->createMock('SomeObject');
        $translator->expects($this->any())
            ->method('someMethod')
            ->willThrowException(new \RuntimeException());
    }
}

?>
