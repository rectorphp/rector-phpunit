<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\PreferPHPUnitThisCallRector\Fixture;

use PHPUnit\Framework\TestCase;

final class ReplaceNoneStaticSkipStaticFunction extends TestCase
{
    public function testMe()
    {
        self::assertSame(1, 1);
    }

    public static function testMe2()
    {
        self::assertSame(1, 1);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\PreferPHPUnitThisCallRector\Fixture;

use PHPUnit\Framework\TestCase;

final class ReplaceNoneStaticSkipStaticFunction extends TestCase
{
    public function testMe()
    {
        $this->assertSame(1, 1);
    }

    public static function testMe2()
    {
        self::assertSame(1, 1);
    }
}

?>
