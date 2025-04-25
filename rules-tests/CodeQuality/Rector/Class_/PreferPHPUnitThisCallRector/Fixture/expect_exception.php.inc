<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\PreferPHPUnitThisCallRector\Fixture;

use PHPUnit\Framework\TestCase;

final class ExpectException extends TestCase
{
    public function test()
    {
        self::expectException('some class');
        self::expectExceptionMessage('some message');

        self::expectExceptionCode(100);
        self::expectExceptionMessageMatches('some regex');
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\PreferPHPUnitThisCallRector\Fixture;

use PHPUnit\Framework\TestCase;

final class ExpectException extends TestCase
{
    public function test()
    {
        $this->expectException('some class');
        $this->expectExceptionMessage('some message');

        $this->expectExceptionCode(100);
        $this->expectExceptionMessageMatches('some regex');
    }
}

?>
