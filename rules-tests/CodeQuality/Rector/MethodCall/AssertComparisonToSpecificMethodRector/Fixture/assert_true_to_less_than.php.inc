<?php

namespace Rector\Tests\PHPUnit\CodeQuality\Rector\MethodCall\AssertComparisonToSpecificMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AssertTrueToLessThan extends TestCase
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

namespace Rector\Tests\PHPUnit\CodeQuality\Rector\MethodCall\AssertComparisonToSpecificMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AssertTrueToLessThan extends TestCase
{
    public function some(int $param)
    {
        self::assertLessThan(0, $param);
        self::assertLessThanOrEqual(0, $param);
    }
}

?>
