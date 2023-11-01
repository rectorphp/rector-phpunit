<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\TestWithToDataProviderRector\Fixture;

use PHPUnit\Framework\TestCase;

class MyTest1 extends TestCase
{
    /**
     * @testWith    ["foo"]
     */
    public function testFirst($value)
    {
    }

    /**
     * @testWith    ["bar"]
     */
    public function testSecond($value)
    {
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\TestWithToDataProviderRector\Fixture;

use PHPUnit\Framework\TestCase;

class MyTest1 extends TestCase
{
    public function dataProviderSecond()
    {
        return [["bar"]];
    }
    public function dataProviderFirst()
    {
        return [["foo"]];
    }
    /**
     * @dataProvider dataProviderFirst
     */
    public function testFirst($value)
    {
    }

    /**
     * @dataProvider dataProviderSecond
     */
    public function testSecond($value)
    {
    }
}

?>
