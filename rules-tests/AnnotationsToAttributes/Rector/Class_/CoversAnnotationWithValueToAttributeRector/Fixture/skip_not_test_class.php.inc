<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\CoversAnnotationWithValueToAttributeRector\Fixture;

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
