<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\MatchAssertSameExpectedTypeRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipDocblockType extends TestCase
{
   public function run()
    {
        $this->assertSame('123', $this->getOrderId());
    }

    /**
     * @return int
     */
    private function getOrderId()
    {
        return '123';
    }
}
