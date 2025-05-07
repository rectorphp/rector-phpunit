<?php

use PHPUnit\Framework\TestCase;

class SomeClassTest extends TestCase
{
    #[\PHPUnit\Framework\Attributes\Test]
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
    #[\PHPUnit\Framework\Attributes\Test]
    public function shouldDoStuff(): void
    {
    }
}

?>
