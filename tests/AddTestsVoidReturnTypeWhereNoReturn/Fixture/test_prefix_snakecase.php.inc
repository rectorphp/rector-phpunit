<?php

use PHPUnit\Framework\TestCase;

class SomeClassTest extends TestCase
{
    public function testShouldDoStuff()
    {
    }
}

?>
-----
<?php

use PHPUnit\Framework\TestCase;

class SomeClassTest extends TestCase
{
    public function testShouldDoStuff(): void
    {
    }
}

?>
