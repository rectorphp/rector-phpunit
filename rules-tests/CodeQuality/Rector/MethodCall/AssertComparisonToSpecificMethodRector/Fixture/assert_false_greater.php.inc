<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertComparisonToSpecificMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AssertFalseGreater extends TestCase
{
    public function some(int $param)
    {
        self::assertFalse($param > 0);

        self::assertFalse($param >= 10);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertComparisonToSpecificMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AssertFalseGreater extends TestCase
{
    public function some(int $param)
    {
        self::assertLessThanOrEqual(0, $param);

        self::assertLessThan(10, $param);
    }
}

?>
