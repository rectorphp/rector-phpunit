<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\MatchAssertSameExpectedTypeRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\MatchAssertSameExpectedTypeRector\Source\Criteria;

final class SkipStaleNarrowedUnionReturnTypeToInt extends TestCase
{
    public function test()
    {
        $criteria = new Criteria();
        assert(is_int($criteria->getType()));

        $criteria->setAnyType(true);

        $this->assertSame('Any', $criteria->getType());
    }
}
