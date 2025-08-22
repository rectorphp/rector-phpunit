<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\Issues\AssertEqualsSame;

use PHPUnit\Framework\TestCase;

class AssertEquals extends TestCase
{
    public function test()
    {
        $this->assertEquals(123, $this->getOrderId());
    }

    private function getOrderId(): string
    {
        return '0000000000000000000123';
    }
}

?>
-----
<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\Issues\AssertEqualsSame;

use PHPUnit\Framework\TestCase;

class AssertEquals extends TestCase
{
    public function test()
    {
        $this->assertEquals('123', $this->getOrderId());
    }

    private function getOrderId(): string
    {
        return '0000000000000000000123';
    }
}

?>