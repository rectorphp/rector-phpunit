<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertEqualsToSameRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AssertNotEquals extends TestCase
{
    public function test()
    {
        $int = 1;
        $expectedInt = 1;
        $this->assertNotEquals($expectedInt, $int);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertEqualsToSameRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AssertNotEquals extends TestCase
{
    public function test()
    {
        $int = 1;
        $expectedInt = 1;
        $this->assertNotSame($expectedInt, $int);
    }
}

?>
