<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

use PHPUnit\Framework\TestCase;

class SkipAssertingSetUp extends TestCase
{
    protected function setUp(): void
    {
        $this->assertTrue(true);
    }

    public function testSomething()
    {
        $value = 5;
    }
}
