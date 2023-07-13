<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertPropertyExistsRector\Fixture;

use Rector\PHPUnit\Tests\AnnotationsToAttributes\Rector\MethodCall\AssertPropertyExistsRector\Fixture\Foo;

final class SkipMethodCall extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $someObject = new Foo();
        self::assertFalse($someObject->someMethod());
    }
}
