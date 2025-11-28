<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertComparisonToSpecificMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AssertTrueToGreaterThan extends TestCase
{
    public function some(int $param)
    {
        self::assertTrue(0 > $param);
        self::assertTrue(0 >= $param);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertComparisonToSpecificMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AssertTrueToGreaterThan extends TestCase
{
    public function some(int $param)
    {
        self::assertGreaterThan($param, 0);
        self::assertGreaterThanOrEqual($param, 0);
    }
}

?>
