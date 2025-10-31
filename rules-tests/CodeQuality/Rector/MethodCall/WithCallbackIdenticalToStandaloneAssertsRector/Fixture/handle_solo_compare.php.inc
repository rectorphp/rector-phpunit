<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\WithCallbackIdenticalToStandaloneAssertsRector\Fixture;

use PHPUnit\Framework\TestCase;

final class HandleSoloCompare extends TestCase
{
    public function test()
    {
        $someMock = $this->createMock('AnyType')
            ->expects($this->any())
            ->method('trans')
            ->with(
                $this->callback(
                    fn ($args): bool => count($args) === 5
                )
            );
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\WithCallbackIdenticalToStandaloneAssertsRector\Fixture;

use PHPUnit\Framework\TestCase;

final class HandleSoloCompare extends TestCase
{
    public function test()
    {
        $someMock = $this->createMock('AnyType')
            ->expects($this->any())
            ->method('trans')
            ->with(
                $this->callback(
                    function ($args): bool {
                        $this->assertCount(5, $args);
                        return true;
                    }
                )
            );
    }
}

?>
