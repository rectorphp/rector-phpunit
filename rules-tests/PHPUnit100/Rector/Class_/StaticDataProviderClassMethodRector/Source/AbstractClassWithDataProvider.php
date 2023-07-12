<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\Class_\StaticDataProviderClassMethodRector\Source;

use PHPUnit\Framework\TestCase;

abstract class AbstractClassWithDataProvider extends TestCase
{
    /**
     * @dataProvider provideData
     */
    public function test(): void
    {

    }

    abstract public function provideData(): array;
}
