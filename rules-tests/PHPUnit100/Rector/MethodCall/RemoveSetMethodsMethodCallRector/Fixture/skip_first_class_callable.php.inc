<?php

namespace Rector\PHPUnit\Tests\PHPUnit100\Rector\MethodCall\RemoveSetMethodsMethodCallRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\PHPUnit100\Rector\MethodCall\RemoveSetMethodsMethodCallRector\Source\SomeClassWithMagicMethods;

final class SkipFirstClassCallable extends TestCase
{
    public function test()
    {
        $someMock = $this->getMockBuilder(SomeClassWithMagicMethods::class)
            ->setMethods(...);
    }
}

?>