<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertEqualsToSameRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipCompareMixed extends TestCase
{
    public function test(mixed $result)
    {
        $this->assertEquals('test', $result);
    }
}
