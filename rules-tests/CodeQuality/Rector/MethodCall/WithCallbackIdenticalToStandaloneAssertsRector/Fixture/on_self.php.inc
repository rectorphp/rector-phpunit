<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\WithCallbackIdenticalToStandaloneAssertsRector\Fixture;

use PHPUnit\Framework\TestCase;

final class OnSelf extends TestCase
{
    public function test()
    {
        $someMock = $this->getMockBuilder('AnyType')->getMock();

        $someMock->expects($this->any())
            ->method('trans')
            ->with($this->callback(fn ($arg) => $arg instanceof self && $arg->isReady()));
    }
}

?>
-----
<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\WithCallbackIdenticalToStandaloneAssertsRector\Fixture;

use PHPUnit\Framework\TestCase;

final class OnSelf extends TestCase
{
    public function test()
    {
        $someMock = $this->getMockBuilder('AnyType')->getMock();

        $someMock->expects($this->any())
            ->method('trans')
            ->with($this->callback(function ($arg): bool {
                $this->assertInstanceOf(self::class, $arg);
                $this->assertTrue($arg->isReady());
                return true;
            }));
    }
}

?>
