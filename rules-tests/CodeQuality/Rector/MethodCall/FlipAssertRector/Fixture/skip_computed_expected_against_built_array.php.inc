<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\FlipAssertRector\Fixture;

final class SkipComputedExpectedAgainstBuiltArray extends \PHPUnit\Framework\TestCase
{
    private array $expectedIds = [];

    private static array $fixtures = [];

    public function test($first, $second, array $expected, $user, $team, $result)
    {
        $this->assertSame($this->expectedIds, [$first->id, $second->id]);
        $this->assertSame($expected['ids'], [$user->id, $team->id]);
        $this->assertSame(static::$fixtures, [$result->name]);
    }
}

?>
