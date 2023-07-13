<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\ClassMethod\DependsAnnotationWithValueToAttributeRector\Fixture;

/**
 * Just random class, not a test class, skip it
 */
class SkipNotTestClass
{
    public function testOne() {}
    /**
     * @depends testOne
     */
    public function testThree(): void
    {
    }
}
