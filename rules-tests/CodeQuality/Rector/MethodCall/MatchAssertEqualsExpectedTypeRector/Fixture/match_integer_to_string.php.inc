<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\MatchAssertEqualsExpectedTypeRector\Fixture;

use PHPUnit\Framework\TestCase;

final class MatchIntegerToString extends TestCase
{
    public function test()
    {
        $this->assertEquals(123, $this->getOrderId());
    }

    private function getOrderId(): string
    {
        return '123';
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\MatchAssertEqualsExpectedTypeRector\Fixture;

use PHPUnit\Framework\TestCase;

final class MatchIntegerToString extends TestCase
{
    public function test()
    {
        $this->assertEquals('123', $this->getOrderId());
    }

    private function getOrderId(): string
    {
        return '123';
    }
}

?>
