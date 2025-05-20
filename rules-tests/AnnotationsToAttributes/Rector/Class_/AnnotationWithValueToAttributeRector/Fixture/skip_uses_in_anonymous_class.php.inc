<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\Class_\AnnotationWithValueToAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipUsedInAnonymousClassTest extends TestCase
{
    public function someTest()
    {
        new class {
            /**
             * @uses Foo::Bar
             */
            public function run()
            {
            }
        };
    }
}
