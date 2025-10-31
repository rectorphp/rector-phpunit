<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\MergeWithCallableAndWillReturnRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipComplexCompare extends TestCase
{
    public function test()
    {
        $this->createMock('SomeClass')
            ->method('someMethod')
            ->with($this->callback(function ($arg) {
                return $arg === 100 && $arg >= 50;
            }))
            ->willReturn('someValue');
    }
}
