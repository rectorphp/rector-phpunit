<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Source;

use PHPUnit\Framework\TestCase;

abstract class AbstractClassWithAssertingTearDown extends TestCase
{
    protected function tearDown(): void
    {
        $this->assertTrue(true);
    }
}
