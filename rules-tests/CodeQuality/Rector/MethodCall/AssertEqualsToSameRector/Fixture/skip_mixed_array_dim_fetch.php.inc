<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertEqualsToSameRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipMixedArrayDimFetch extends TestCase
{
    public function test()
    {
        $data = $this->getData();
        $this->assertEquals(1.0, $data[0]);
    }

    private function getData(): array
    {
        return [1];
    }
}
