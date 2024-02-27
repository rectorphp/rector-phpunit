<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\UseSpecificWillMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class WillReturnMapObject extends TestCase
{
    public function test()
    {
        $translator = $this->createMock('SomeObject');
        $translator->expects($this->any())
            ->method('someMethod')
            ->will(new \PHPUnit\Framework\MockObject\Stub\ReturnValueMap([]));
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\UseSpecificWillMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class WillReturnMapObject extends TestCase
{
    public function test()
    {
        $translator = $this->createMock('SomeObject');
        $translator->expects($this->any())
            ->method('someMethod')
            ->willReturnMap([]);
    }
}

?>
