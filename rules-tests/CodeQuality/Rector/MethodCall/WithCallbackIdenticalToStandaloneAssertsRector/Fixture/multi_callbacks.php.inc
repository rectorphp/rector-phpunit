<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\WithCallbackIdenticalToStandaloneAssertsRector\Fixture;

use PHPUnit\Framework\TestCase;

final class MultiCallbacks extends TestCase
{
    public function test()
    {
        $someMock = $this->getMockBuilder('AnyType')->getMock();

        $someMock->expects($this->any())
            ->method('trans')
            ->with(
                    $this->callback(fn (array $args) => array_key_exists(5, $args)),
                    $this->callback(fn (array $args) => array_key_exists(50, $args)),
            );
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\WithCallbackIdenticalToStandaloneAssertsRector\Fixture;

use PHPUnit\Framework\TestCase;

final class MultiCallbacks extends TestCase
{
    public function test()
    {
        $someMock = $this->getMockBuilder('AnyType')->getMock();

        $someMock->expects($this->any())
            ->method('trans')
            ->with(
                    $this->callback(function (array $args): bool {
                        $this->assertArrayHasKey(5, $args);
                        return true;
                    }),
                    $this->callback(function (array $args): bool {
                        $this->assertArrayHasKey(50, $args);
                        return true;
                    }),
            );
    }
}

?>
