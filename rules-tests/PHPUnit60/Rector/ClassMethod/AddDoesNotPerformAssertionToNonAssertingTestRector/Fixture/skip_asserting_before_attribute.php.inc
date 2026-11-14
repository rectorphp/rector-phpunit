<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

use PHPUnit\Framework\Attributes\Before;
use PHPUnit\Framework\TestCase;

class SkipAssertingBeforeAttribute extends TestCase
{
    #[Before]
    protected function prepare(): void
    {
        $this->assertTrue(true);
    }

    public function testSomething()
    {
        $value = 5;
    }
}
