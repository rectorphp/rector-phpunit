<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertEmptyNullableObjectToAssertInstanceofRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipNoArg extends TestCase
{
    public function test()
    {
        $this->assertEmpty();
    }
}