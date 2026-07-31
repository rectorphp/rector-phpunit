<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\ClassMethod\DataProviderAnnotationToAttributeRector\Fixture;

trait SkipNonPublicTraitMethod
{
    /**
     * @dataProvider someMethod()
     */
    protected function test(): void
    {
    }
}
