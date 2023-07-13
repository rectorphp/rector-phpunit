<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertFalseStrposToContainsRector\Fixture;

use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertFalseStrposToContainsRector\Fixture\Foo;

final class SkipMethodCall extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $someObject = new Foo();
        self::assertFalse($someObject->someMethod());
    }
}
