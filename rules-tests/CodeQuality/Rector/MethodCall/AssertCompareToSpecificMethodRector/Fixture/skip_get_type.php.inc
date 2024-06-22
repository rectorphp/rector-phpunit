<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertCompareToSpecificMethodRector\Fixture;

final class SkipGetType extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $value = 'some';
        $this->assertNotSame('resource', gettype($value));
    }
}
