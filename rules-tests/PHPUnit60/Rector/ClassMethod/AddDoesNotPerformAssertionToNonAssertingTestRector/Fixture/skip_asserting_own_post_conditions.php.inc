<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

use PHPUnit\Framework\TestCase;

class SkipAssertingOwnPostConditions extends TestCase
{
    protected function assertPostConditions(): void
    {
        $this->assertTrue(true);
    }

    public function testSomething()
    {
        $value = 5;
    }
}
