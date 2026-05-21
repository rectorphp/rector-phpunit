<?php

// skip: non-string argument (enum case) should not crash

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\Class_\AssertIsTypeMethodCallRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipNonPHPUnitType extends TestCase
{
    public function testMethod(\stdClass $else): void
    {
        $else->isType('string');
        $else->isType('array');
        $else->isType();
    }
}
