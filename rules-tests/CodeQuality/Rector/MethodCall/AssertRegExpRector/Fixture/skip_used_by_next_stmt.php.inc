<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertRegExpRector\Fixture;

final class SkipUsedByNextStmt extends \PHPUnit\Framework\TestCase
{
    public function testFoo(): void
    {
    	$string = 'keys=1000';

        $this->assertSame(1, preg_match('/^keys=(?P<count>\d+)/', $string, $matches));
        $this->assertSame(1000, (int) $matches['count']);
    }
}