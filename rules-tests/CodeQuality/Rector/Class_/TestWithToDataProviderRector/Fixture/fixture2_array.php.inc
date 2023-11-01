<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\TestWithToDataProviderRector\Fixture;

use PHPUnit\Framework\TestCase;

class MyTest1 extends TestCase
{
    /**
     * @testWith    [[{"fieldA":"foo", "fieldB":"bar", "fieldC":1},{"fieldA":"foo", "fieldB":"bar", "fieldC":2}]]
     * @testWith    [[{"fieldA":"foo", "fieldC":1}]]
     */
    public function test(array $a)
    {
        $this->assertIsArray($a);
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
        return [[[['fieldA' => "foo", 'fieldB' => "bar", 'fieldC' => 1], ['fieldA' => "foo", 'fieldB' => "bar", 'fieldC' => 2]]], [[['fieldA' => "foo", 'fieldC' => 1]]]];
    }
    /**
     * @dataProvider dataProvider
     */
    public function test(array $a)
    {
        $this->assertIsArray($a);
    }
}

?>
