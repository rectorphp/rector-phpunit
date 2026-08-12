<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

use PHPUnit\Framework\TestCase;

use function PHPUnit\Framework\assertNotNull;

final class SkipImportedAssertFunction extends TestCase
{
    public function testSomething(): void
    {
        assertNotNull(true);
    }

    public function testFullyQualified(): void
    {
        \PHPUnit\Framework\assertTrue(true);
    }
}
