<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\ScalarArgumentToExpectedParamTypeRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\ScalarArgumentToExpectedParamTypeRector\Source\SomeClassWithSetter;

final class SkipUnionType extends TestCase
{
    public function test()
    {
        $someClassWithSetter = new SomeClassWithSetter();
        $someClassWithSetter->setUnionType(123456);
    }
}
