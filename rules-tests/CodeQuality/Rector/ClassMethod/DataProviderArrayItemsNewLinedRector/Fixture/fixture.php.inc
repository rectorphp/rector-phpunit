<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\DataProviderArrayItemsNewLinedRector\Fixture;

class SomeTest extends \PHPUnit\Framework\TestCase
{
    public function dataProviderFoo()
    {
        return [[1], [2], [3]];
    }

    /**
     * @dataProvider dataProviderFoo
     */
    public function testFoo(int $value)
    {
        $this->assertGreaterThan(0, $value);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\DataProviderArrayItemsNewLinedRector\Fixture;

class SomeTest extends \PHPUnit\Framework\TestCase
{
    public function dataProviderFoo()
    {
        return [
            [1],
            [2],
            [3],
        ];
    }

    /**
     * @dataProvider dataProviderFoo
     */
    public function testFoo(int $value)
    {
        $this->assertGreaterThan(0, $value);
    }
}

?>
