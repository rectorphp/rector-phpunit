<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\FlipAssertRector\Fixture;

final class NegativeNumber extends \PHPUnit\Framework\TestCase
{
    private const LIMIT = 10;

    public function test($result, $model, $response, $transformations)
    {
        $this->assertSame($result->getOffset(), -1);
        $this->assertSame($result->getMin(), -PHP_INT_MAX);
        $this->assertSame($result->getLimit(), -self::LIMIT);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\FlipAssertRector\Fixture;

final class NegativeNumber extends \PHPUnit\Framework\TestCase
{
    private const LIMIT = 10;

    public function test($result, $model, $response, $transformations)
    {
        $this->assertSame(-1, $result->getOffset());
        $this->assertSame(-PHP_INT_MAX, $result->getMin());
        $this->assertSame(-self::LIMIT, $result->getLimit());
    }
}

?>
