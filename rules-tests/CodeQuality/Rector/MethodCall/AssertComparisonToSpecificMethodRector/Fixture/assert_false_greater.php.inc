<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertComparisonToSpecificMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AssertTrueToLessThan extends TestCase
{
    public function some(int $param)
    {
        self::assertTrue(0 < $param);
        self::assertTrue(0 <= $param);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertComparisonToSpecificMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AssertTrueToLessThan extends TestCase
{
    public function some(int $param)
    {
        self::assertLessThan($param, 0);
        self::assertLessThanOrEqual($param, 0);
    }
}

?>
