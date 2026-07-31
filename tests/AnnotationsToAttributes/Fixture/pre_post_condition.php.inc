<?php

use PHPUnit\Framework\TestCase;

class PrePostConditionTest extends TestCase
{
    /**
     * @preCondition
     */
    protected function setUpSomething()
    {
    }

    /**
     * @postCondition
     */
    protected function tearDownSomething()
    {
    }
}

?>
-----
<?php

use PHPUnit\Framework\TestCase;

class PrePostConditionTest extends TestCase
{
    #[\PHPUnit\Framework\Attributes\PreCondition]
    protected function setUpSomething()
    {
    }

    #[\PHPUnit\Framework\Attributes\PostCondition]
    protected function tearDownSomething()
    {
    }
}

?>
