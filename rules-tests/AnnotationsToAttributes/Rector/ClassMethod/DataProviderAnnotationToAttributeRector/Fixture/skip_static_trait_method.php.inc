<?php

namespace Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\ClassMethod\DataProviderAnnotationToAttributeRector\Fixture;

trait SkipStaticTraitMethod
{
    /**
     * @dataProvider someMethod()
     */
    public static function test(): void
    {
    }
}
