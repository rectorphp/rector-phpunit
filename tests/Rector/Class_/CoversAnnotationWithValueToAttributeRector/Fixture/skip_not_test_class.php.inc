<?php

namespace Rector\PHPUnit\Tests\Rector\Class_\AnnotationWithValueToAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipNotTestClass
{
    /**
     * @covers ::someFunction()
     */
    public function test()
    {
    }
}
