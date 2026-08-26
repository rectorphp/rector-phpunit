<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertTrueFalseToSpecificMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipIsCallableWithSyntaxOnly extends TestCase
{
    public function test()
    {
        $this->assertTrue(is_callable($value, true));
        $this->assertTrue(is_callable($value, true, $callableName));
    }
}
