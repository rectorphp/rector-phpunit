<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\PreferTestsWithCamelCaseRector\Fixture;

use PHPUnit\Framework\TestCase;

final class RenameTest extends TestCase
{
    public function test_me()
    {
    }

    public function test_this_is_a_long_test_case()
    {
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\PreferTestsWithCamelCaseRector\Fixture;

use PHPUnit\Framework\TestCase;

final class RenameTest extends TestCase
{
    public function testMe()
    {
    }

    public function testThisIsALongTestCase()
    {
    }
}

?>
