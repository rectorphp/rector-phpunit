<?php

namespace Rector\PHPUnit\Tests\Rector\Class_\StaticDataProviderClassMethodRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\Rector\Class_\StaticDataProviderClassMethodRector\Source\SomeClassToMock;

final class SkipContainingThis extends TestCase
{
    /**
     * @dataProvider provideData()
     */
    public function test()
    {
    }

    public function provideData()
    {
        $mock = $this->createMock(SomeClassToMock::class);

        yield 'thing generated' => [$mock];
    }
}
