<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\WithCallbackIdenticalToStandaloneAssertsRector\Fixture;

use PHPUnit\Framework\TestCase;

final class HandleSoloIsset extends TestCase
{
    public function test()
    {
        $someMock = $this->createMock('AnyType')
            ->expects($this->any())
            ->method('trans')
            ->with(
                $this->callback(
                    fn ($args): bool => isset($args['key'])
                )
            );
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\WithCallbackIdenticalToStandaloneAssertsRector\Fixture;

use PHPUnit\Framework\TestCase;

final class HandleSoloIsset extends TestCase
{
    public function test()
    {
        $someMock = $this->createMock('AnyType')
            ->expects($this->any())
            ->method('trans')
            ->with(
                $this->callback(
                    function ($args): bool {
                        $this->assertArrayHasKey('key', $args);
                        return true;
                    }
                )
            );
    }
}

?>
