<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertEqualsToSameRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipUnionType extends TestCase
{
    public function test(string|int|bool|\DateTime $expected)
    {
        $this->assertEquals('value', $this->normalizeStringValue($expected));
    }

    private function normalizeStringValue(string|int|bool|\DateTime $input): string|int|bool|\DateTime
    {
        return $input;
    }
}
