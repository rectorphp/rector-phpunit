<?php

use PHPUnit\Framework\TestCase;

class SomeClassTest extends TestCase
{
    /** @test */
    public function shouldDoStuff()
    {
    }
}

?>
-----
<?php

use PHPUnit\Framework\TestCase;

class SomeClassTest extends TestCase
{
    /** @test */
    public function shouldDoStuff(): void
    {
    }
}

?>
