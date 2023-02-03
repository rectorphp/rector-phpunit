<?php

use PHPUnit\Framework\TestCase;

class DataProviderAttributeRemoveBrackets extends TestCase
{
    /**
     * @dataProvider thisMethod()
     */
    public function shouldDoStuff()
    {
    }
}

?>
-----
<?php

use PHPUnit\Framework\TestCase;

class DataProviderAttributeRemoveBrackets extends TestCase
{
    #[\PHPUnit\Framework\Attributes\DataProvider('thisMethod')]
    public function shouldDoStuff()
    {
    }
}

?>
