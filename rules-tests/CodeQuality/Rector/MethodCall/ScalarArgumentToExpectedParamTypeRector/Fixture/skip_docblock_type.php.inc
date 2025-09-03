<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\ScalarArgumentToExpectedParamTypeRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\ScalarArgumentToExpectedParamTypeRector\Source\SomeClassWithSetter;

final class SkipDocblockType extends TestCase
{
    public function test()
    {
        $someClassWithSetter = new SomeClassWithSetter();
        $someClassWithSetter->setMagicType(123456);
    }
}
