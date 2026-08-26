<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertTrueFalseToSpecificMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipNamedAndSpreadArgs extends TestCase
{
    public function test()
    {
        $this->assertTrue(is_string(value: $value));
        $this->assertTrue(is_readable(filename: $file));
        $this->assertTrue(is_string(...$args));
        $this->assertTrue(is_string(...));
        $this->assertTrue(in_array(needle: '...', haystack: ['...'], strict: true));
    }
}
