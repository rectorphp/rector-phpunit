<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\CallLike\DirectInstanceOverMockArgRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SomeCrashArray extends TestCase
{
    private const array TIME_UNITS = [
        ['weeks', 604800],
        ['days', 86400],
        ['hours', 3600],
        ['minutes', 60],
        ['seconds', 1],
    ];

    public function testThat($product)
    {
        foreach (self::TIME_UNITS as [$unit, $seconds]) {
            if ($product % $seconds === 0) {
                return [
                    'unit' => (string) $unit,
                    'value' => (int) ($product / $seconds),
                ];
            }
        }
    }
}
