<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertPropertyExistsRector\Fixture;

use Rector\PHPUnit\Tests\Rector\MethodCall\AssertPropertyExistsRector\Fixture\SomeClass;

final class SkipStaticCall extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        self::assertFalse(SomeClass::someMethod());
    }
}
