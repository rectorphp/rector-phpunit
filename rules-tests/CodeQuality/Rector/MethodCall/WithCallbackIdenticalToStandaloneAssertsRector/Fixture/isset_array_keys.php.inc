<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\WithCallbackIdenticalToStandaloneAssertsRector\Fixture;

use PHPUnit\Framework\TestCase;

final class IssetArrayKeys extends TestCase
{
    public function test()
    {
        $someMock = $this->getMockBuilder('AnyType')->getMock();

        $someMock->expects($this->any())
            ->method('trans')
            ->with($this->callback(function ($args): bool {
                return count($args) === 5 && isset($args[0]) && $args[0] === 'some_value';
            }));
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\WithCallbackIdenticalToStandaloneAssertsRector\Fixture;

use PHPUnit\Framework\TestCase;

final class IssetArrayKeys extends TestCase
{
    public function test()
    {
        $someMock = $this->getMockBuilder('AnyType')->getMock();

        $someMock->expects($this->any())
            ->method('trans')
            ->with($this->callback(function ($args): bool {
                $this->assertCount(5, $args);
                $this->assertArrayHasKey(0, $args);
                $this->assertSame('some_value', $args[0]);
                return true;
            }));
    }
}

?>
