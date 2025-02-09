<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertCountWithZeroToAssertEmptyRector\Source;

class Collection implements \Countable
{
    public function count(): int
    {
        return 0;
    }
}
