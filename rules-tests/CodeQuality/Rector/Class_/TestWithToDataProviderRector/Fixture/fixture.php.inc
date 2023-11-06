<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\TestWithToDataProviderRector\Fixture;

use PHPUnit\Framework\TestCase;

class MyTest1 extends TestCase
{
    /**
     * @testWith    [0, 0, 0]
     * @testWith    [0, 1, 1]
     * @testWith    [1, 0, 1]
     * @testWith    [1, 1, 3]
     */
    public function testFoo(int $a, int $b, int $expected)
    {
        $this->assertSame($expected, $a + $b);
    }

    /**
     * @testWith    [0, 0, 0]
     *              [0, 1, 1]
     *              [1, 0, 1]
     *              [1, 1, 3]
     */
    public function testBar(int $a, int $b, int $expected)
    {
        $this->assertSame($expected, $a + $b);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\TestWithToDataProviderRector\Fixture;

use PHPUnit\Framework\TestCase;

class MyTest1 extends TestCase
{
    public function dataProviderBar()
    {
        return [[0, 0, 0], [0, 1, 1], [1, 0, 1], [1, 1, 3]];
    }
    public function dataProviderFoo()
    {
        return [[0, 0, 0], [0, 1, 1], [1, 0, 1], [1, 1, 3]];
    }
    /**
     * @dataProvider dataProviderFoo
     */
    public function testFoo(int $a, int $b, int $expected)
    {
        $this->assertSame($expected, $a + $b);
    }

    /**
     * @dataProvider dataProviderBar
     */
    public function testBar(int $a, int $b, int $expected)
    {
        $this->assertSame($expected, $a + $b);
    }
}

?>
