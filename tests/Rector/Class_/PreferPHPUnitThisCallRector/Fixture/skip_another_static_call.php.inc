<?php

namespace Rector\PHPUnit\Tests\Rector\Class_\PreferPHPUnitThisCallRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipAnotherStaticCall extends TestCase
{
    public function testMe()
    {
        $results = self::getResults();
    }

    public static function getResults()
    {
        return [1, 2];
    }
}
