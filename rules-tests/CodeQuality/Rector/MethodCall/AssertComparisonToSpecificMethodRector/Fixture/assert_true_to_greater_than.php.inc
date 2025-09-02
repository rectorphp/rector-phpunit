<?php
namespace Rector\Tests\PHPUnit\CodeQuality\Rector\MethodCall\AssertComparisonToSpecificMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AssertTrueToGreaterThan extends TestCase
{
    public function some(int $param)
    {
        self::assertTrue(0 < $param);
    }

}
?>
-----
<?php

namespace Rector\Tests\PHPUnit\CodeQuality\Rector\MethodCall\AssertComparisonToSpecificMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AssertTrueToGreaterThan extends TestCase
{
    public function some(int $param)
    {
        self::assertGreaterThan(0, $param);
    }
}

?>
