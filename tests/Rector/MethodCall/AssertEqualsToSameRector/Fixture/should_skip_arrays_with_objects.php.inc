<?php

use PHPUnit\Framework\TestCase;

namespace Rector\Tests\PHPUnit\Rector\MethodCall\AssertEqualsToSameRector\Fixture;

final class ShouldSkipArraysWithObjects extends TestCase
{
    public function test()
    {
        $expected = ['date' => new DateTimeImmutable('2022-10-31 12:32:33')];
        $date = new DateTimeImmutable('2022-10-31 12:32:33');
        $actual = compact('date');

        self::assertEquals($expected, $actual);
    }
}

?>
