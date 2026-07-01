<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\ChangeMockObjectReturnUnionToIntersectionRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipNonMockUnionTest extends TestCase
{
    /**
     * @return Event|Campaign
     */
    private function resolve()
    {
        return $this->createEvent();
    }
}
