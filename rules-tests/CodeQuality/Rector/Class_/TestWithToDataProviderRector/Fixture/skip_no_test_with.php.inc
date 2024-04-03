<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\TestWithToDataProviderRector\Fixture;

use PHPUnit\Framework\TestCase;

class SkipNoTestWith extends TestCase
{
    public function testFoo(int $a, int $b, int $expected)
    {
        $this->assertSame($expected, $a + $b);
    }
}
