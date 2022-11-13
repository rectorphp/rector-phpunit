<?php

use PHPUnit\Framework\TestCase;

/**
 * @small
 */
class BarController extends TestCase
{
    /**
     * @test
     */
    public function shouldDoStuff()
    {
    }
}

?>
-----
<?php

use PHPUnit\Framework\TestCase;

#[\PHPUnit\Framework\Attributes\Small]
class BarController extends TestCase
{
    #[\PHPUnit\Framework\Attributes\Test]
    public function shouldDoStuff()
    {
    }
}

?>
