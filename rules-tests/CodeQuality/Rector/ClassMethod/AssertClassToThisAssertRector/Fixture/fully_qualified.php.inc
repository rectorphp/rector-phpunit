<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\AssertClassToThisAssertRector\Fixture;

use PHPUnit\Framework\TestCase;

final class FullyQualifiedTest extends TestCase
{
    public function testMe()
    {
        \PHPUnit\Framework\Assert::assertEquals('expected', $result);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\AssertClassToThisAssertRector\Fixture;

use PHPUnit\Framework\TestCase;

final class FullyQualifiedTest extends TestCase
{
    public function testMe()
    {
        $this->assertEquals('expected', $result);
    }
}

?>
