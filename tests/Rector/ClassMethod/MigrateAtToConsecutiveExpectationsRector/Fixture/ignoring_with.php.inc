<?php

namespace Rector\PHPUnit\Tests\Rector\ClassMethod\MigrateAtToConsecutiveExpectationsRector\Fixture;

use PHPUnit\Framework\TestCase;

final class IgnoringWith extends TestCase
{
    public function barTest()
    {
        $query
            ->expects($this->at(0))
            ->method('get')
            ->with('signed')
            ->will($this->returnValue($signed));
    }
}
?>
-----
<?php

namespace Rector\PHPUnit\Tests\Rector\ClassMethod\MigrateAtToConsecutiveExpectationsRector\Fixture;

use PHPUnit\Framework\TestCase;

final class IgnoringWith extends TestCase
{
    public function barTest()
    {
        $query
            ->method('get')
            ->with('signed')
            ->willReturnOnConsecutiveCalls($this->returnValue($signed));
    }
}
?>
