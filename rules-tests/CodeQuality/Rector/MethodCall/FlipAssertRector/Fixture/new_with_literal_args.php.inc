<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\FlipAssertRector\Fixture;

final class NewWithLiteralArgs extends \PHPUnit\Framework\TestCase
{
    public function test($result)
    {
        $this->assertEquals($result, new Money(100, Currency::EUR));
        $this->assertEquals($result->getPeriod(), new Period(['from' => 1, 'to' => -1]));
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\FlipAssertRector\Fixture;

final class NewWithLiteralArgs extends \PHPUnit\Framework\TestCase
{
    public function test($result)
    {
        $this->assertEquals(new Money(100, Currency::EUR), $result);
        $this->assertEquals(new Period(['from' => 1, 'to' => -1]), $result->getPeriod());
    }
}

?>
