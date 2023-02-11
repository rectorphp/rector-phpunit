<?php

namespace Rector\PHPUnit\Tests\Rector\Class_\StaticDataProviderClassMethodRector\Source;

use PHPUnit\Framework\TestCase;

abstract class AnotherAbstractClass extends TestCase
{
    /**
     * @dataProvider dataProvider
     */
    public function testWithDataProvider($value1, $value2): void
    {

    }

    abstract public function dataProvider(): array;
}
