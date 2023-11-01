<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\TestWithToDataProviderRector\Fixture;

use PHPUnit\Framework\TestCase;

class MyTest1 extends TestCase
{
    /**
     * @testWith    ["foo"]
     * @testWith    [2.2]
     * @testWith    [true]
     * @testWith    [null]
     */
    public function test($value)
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
    public function dataProvider()
    {
        return [["foo"], [2.2], [true], [null]];
    }
    /**
     * @dataProvider dataProvider
     */
    public function test($value)
    {
    }
}

?>
