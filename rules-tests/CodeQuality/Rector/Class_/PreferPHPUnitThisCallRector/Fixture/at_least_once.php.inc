<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\PreferPHPUnitThisCallRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AtLeastOnce extends TestCase
{
    public function testMe()
    {
        $matcher = self::once();
        $matcher = self::atLeast(5);
        $matcher = self::never();
        $matcher = self::atLeastOnce();
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\PreferPHPUnitThisCallRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AtLeastOnce extends TestCase
{
    public function testMe()
    {
        $matcher = $this->once();
        $matcher = $this->atLeast(5);
        $matcher = $this->never();
        $matcher = $this->atLeastOnce();
    }
}

?>
