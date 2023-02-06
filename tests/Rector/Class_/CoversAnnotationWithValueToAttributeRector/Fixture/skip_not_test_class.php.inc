<?php

namespace Rector\PHPUnit\Tests\Rector\Class_\CoversAnnotationWithValueToAttributeRector\Fixture;

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
