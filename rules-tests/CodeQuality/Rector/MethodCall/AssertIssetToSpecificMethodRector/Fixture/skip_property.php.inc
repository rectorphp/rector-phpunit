<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertIssetToSpecificMethodRector\Fixture;

final class SkipProperty extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $this->assertTrue(isset($node->value1));
        $this->assertFalse(isset($node->value2), 'message');
    }
}
