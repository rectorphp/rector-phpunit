<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\StringCastAssertStringContainsStringRector\Fixture;

use PHPUnit\Framework\TestCase;

class SkipKnownString extends TestCase
{
    public function testSomething(string $value)
    {
        $this->assertStringContainsString('foo', $value);
    }
}
