<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertFalseStrposToContainsRector\Fixture;

use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertFalseStrposToContainsRector\Fixture\SomeClass;

final class SkipStaticCall extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        self::assertFalse(SomeClass::someMethod());
    }
}
