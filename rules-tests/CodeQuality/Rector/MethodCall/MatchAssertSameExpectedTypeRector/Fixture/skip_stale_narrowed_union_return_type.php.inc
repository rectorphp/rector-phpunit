<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\MatchAssertSameExpectedTypeRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\MatchAssertSameExpectedTypeRector\Source\Criteria;

final class SkipStaleNarrowedUnionReturnType extends TestCase
{
    public function test()
    {
        $criteria = new Criteria();
        assert(is_string($criteria->getType()));

        $criteria->setTypeId(100);

        $this->assertSame(100, $criteria->getType());
    }
}
