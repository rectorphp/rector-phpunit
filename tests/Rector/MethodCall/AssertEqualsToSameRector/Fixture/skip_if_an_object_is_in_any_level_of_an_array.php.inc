<?php

namespace Rector\Tests\PHPUnit\Rector\MethodCall\AssertEqualsToSameRector\Fixture;

use PHPUnit\Framework\TestCase;

final class Test extends TestCase
{
    public function test()
    {
        $expected = ['something' => ['date' => new DateTimeImmutable('2022-10-31 12:32:33')]];
        $date = new DateTimeImmutable('2022-10-31 12:32:33');
        $actual = compact('date');

        self::assertEquals($expected, $actual);
    }
}

?>
