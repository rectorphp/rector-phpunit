<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\PreferPHPUnitSelfCallRector\Fixture;

use PHPUnit\Framework\TestCase;

final class IncludeExceptions extends TestCase
{
    public function testMe()
    {
        $this->expectException(\RuntimeException::class);
        $this->expectExceptionMessage('foo');
        $this->expectExceptionCode(123);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\PreferPHPUnitSelfCallRector\Fixture;

use PHPUnit\Framework\TestCase;

final class IncludeExceptions extends TestCase
{
    public function testMe()
    {
        self::expectException(\RuntimeException::class);
        self::expectExceptionMessage('foo');
        self::expectExceptionCode(123);
    }
}

?>
