<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertTrueFalseToSpecificMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class FileExists extends TestCase
{
    public function test()
    {
        $this->assertTrue(file_exists($file));
        $this->assertFalse(file_exists($file));
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertTrueFalseToSpecificMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class FileExists extends TestCase
{
    public function test()
    {
        $this->assertFileExists($file);
        $this->assertFileDoesNotExist($file);
    }
}

?>
