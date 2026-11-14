<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

use PHPUnit\Framework\TestCase;
use PHPUnit\Framework\Attributes as PU;

final class AliasBefore extends TestCase
{
    #[PU\Before]
    protected function check(): void
    {
        $this->assertTrue(true);
    }

    public function testSomething()
    {
        $value = 1;
    }
}
