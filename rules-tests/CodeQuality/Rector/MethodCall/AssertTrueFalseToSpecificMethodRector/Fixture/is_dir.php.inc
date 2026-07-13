<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertTrueFalseToSpecificMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class IsDir extends TestCase
{
    public function test()
    {
        $this->assertTrue(is_dir($directory));
        $this->assertFalse(is_dir($directory));
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertTrueFalseToSpecificMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class IsDir extends TestCase
{
    public function test()
    {
        $this->assertDirectoryExists($directory);
        $this->assertDirectoryDoesNotExist($directory);
    }
}

?>
