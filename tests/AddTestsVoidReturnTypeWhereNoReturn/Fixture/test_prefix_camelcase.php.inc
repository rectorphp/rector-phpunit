<?php

use PHPUnit\Framework\TestCase;

class SomeClassTest extends TestCase
{
    public function test_should_do_stuff()
    {
    }
}

?>
-----
<?php

use PHPUnit\Framework\TestCase;

class SomeClassTest extends TestCase
{
    public function test_should_do_stuff(): void
    {
    }
}

?>
