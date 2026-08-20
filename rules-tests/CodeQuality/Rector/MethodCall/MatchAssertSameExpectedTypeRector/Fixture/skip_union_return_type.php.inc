<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\MatchAssertSameExpectedTypeRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\MatchAssertSameExpectedTypeRector\Source\Criteria;

final class SkipUnionReturnType extends TestCase
{
    public function test()
    {
        $criteria = new Criteria();

        $this->assertSame(100, $criteria->getType());
    }
}
