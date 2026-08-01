<?php

use PHPUnit\Framework\TestCase;

final class VersionBoundMethodRenamesTest extends TestCase
{
    public function testSomething()
    {
        $this->assertObjectHasAttribute('someProperty', new stdClass());
        $this->expectExceptionMessage('some message');
    }
}

?>
-----
<?php

use PHPUnit\Framework\TestCase;

final class VersionBoundMethodRenamesTest extends TestCase
{
    public function testSomething()
    {
        $this->assertObjectHasProperty('someProperty', new stdClass());
        $this->expectExceptionMessageIsOrContains('some message');
    }
}

?>
