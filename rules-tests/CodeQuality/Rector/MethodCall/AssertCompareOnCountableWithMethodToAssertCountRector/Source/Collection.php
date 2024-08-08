<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertCompareOnCountableWithMethodToAssertCountRector\Source;

class Collection implements \Countable
{
    public function count(): int
    {
        return 0;
    }
}
