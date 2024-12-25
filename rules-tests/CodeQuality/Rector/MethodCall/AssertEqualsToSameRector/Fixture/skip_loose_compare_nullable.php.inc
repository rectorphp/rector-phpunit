<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertEqualsToSameRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipLooseCompareNullable extends TestCase
{
    public function test()
    {
        $this->assertEquals(1.0, $this->get());
    }

    private function get(): ?int
    {
        return 1;
    }
}
