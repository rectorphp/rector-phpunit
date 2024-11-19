<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\PreferPHPUnitThisCallRector\Fixture;

use PHPUnit\Framework\TestCase;

final class CreateMock extends TestCase
{
    public function testMe()
    {
        $someMock = self::createMock('stdClass');
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\PreferPHPUnitThisCallRector\Fixture;

use PHPUnit\Framework\TestCase;

final class CreateMock extends TestCase
{
    public function testMe()
    {
        $someMock = $this->createMock('stdClass');
    }
}

?>
