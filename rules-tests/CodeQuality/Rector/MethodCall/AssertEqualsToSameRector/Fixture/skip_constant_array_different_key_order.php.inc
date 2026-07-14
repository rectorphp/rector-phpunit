<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertEqualsToSameRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipConstantArrayDifferentKeyOrder extends TestCase
{
    public function test()
    {
        $expected = ['pack_keys' => 'DEFAULT', 'row_format' => 'REDUNDANT'];
        $actual = ['row_format' => 'REDUNDANT', 'pack_keys' => 'DEFAULT'];
        $this->assertEquals($expected, $actual);
    }
}

?>
