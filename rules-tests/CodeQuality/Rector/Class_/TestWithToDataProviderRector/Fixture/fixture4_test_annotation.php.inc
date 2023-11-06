<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\TestWithToDataProviderRector\Fixture;

use PHPUnit\Framework\TestCase;

class MyTest1 extends TestCase
{
    /**
     * @test
     * @testWith    ["foo"]
     */
    public function someOtherTestWithoutPrefix($value)
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
    public function dataProviderSomeOtherTestWithoutPrefix()
    {
        return [["foo"]];
    }
    /**
     * @test
     * @dataProvider dataProviderSomeOtherTestWithoutPrefix
     */
    public function someOtherTestWithoutPrefix($value)
    {
    }
}

?>
