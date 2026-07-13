<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertEqualsToSameRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipConstantArrayUnknownActual extends TestCase
{
    public function test(array $result)
    {
        $expected = [1 => 2];
        $this->assertEquals($expected, $result);
    }
}

?>
