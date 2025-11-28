<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertEqualsToSameRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\Rector\MethodCall\AssertEqualsToSameRector\Fixture\DateTimeImmutable;

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
