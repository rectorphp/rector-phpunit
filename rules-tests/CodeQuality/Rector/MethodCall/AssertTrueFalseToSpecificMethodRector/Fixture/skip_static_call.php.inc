<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertTrueFalseToSpecificMethodRector\Fixture;

use Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\MethodCall\AssertTrueFalseToSpecificMethodRector\Fixture\SomeClass;

final class SkipStaticCall extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        self::assertFalse(SomeClass::someMethod());
    }
}
