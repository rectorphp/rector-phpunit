<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertEqualsToSameRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipArraysWithObjects extends TestCase
{
    public function test()
    {
        $expected = ['date' => new \DateTimeImmutable('2022-10-31 12:32:33')];
        $date = new \DateTimeImmutable('2022-10-31 12:32:33');
        $actual = compact('date');

        self::assertEquals($expected, $actual);
    }
}

?>
