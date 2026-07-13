<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertEqualsToSameRector\Fixture;

use PHPUnit\Framework\TestCase;

final class ConstantArraySameKeyOrder extends TestCase
{
    public function test()
    {
        $expected = ['pack_keys' => 'DEFAULT', 'row_format' => 'REDUNDANT'];
        $actual = ['pack_keys' => 'DEFAULT', 'row_format' => 'REDUNDANT'];
        $this->assertEquals($expected, $actual);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertEqualsToSameRector\Fixture;

use PHPUnit\Framework\TestCase;

final class ConstantArraySameKeyOrder extends TestCase
{
    public function test()
    {
        $expected = ['pack_keys' => 'DEFAULT', 'row_format' => 'REDUNDANT'];
        $actual = ['pack_keys' => 'DEFAULT', 'row_format' => 'REDUNDANT'];
        $this->assertSame($expected, $actual);
    }
}

?>
