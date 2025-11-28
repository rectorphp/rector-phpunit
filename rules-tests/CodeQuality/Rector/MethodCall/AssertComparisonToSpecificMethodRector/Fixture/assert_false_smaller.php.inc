<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertComparisonToSpecificMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AssertFalseSmaller extends TestCase
{
    public function some(int $param)
    {
        self::assertFalse(0 < $param);

        self::assertFalse(10 <= $param);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertComparisonToSpecificMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AssertFalseSmaller extends TestCase
{
    public function some(int $param)
    {
        self::assertGreaterThanOrEqual($param, 0);

        self::assertGreaterThan($param, 10);
    }
}

?>
