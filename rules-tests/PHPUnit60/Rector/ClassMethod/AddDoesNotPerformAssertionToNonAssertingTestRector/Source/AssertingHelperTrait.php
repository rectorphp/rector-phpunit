<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Source;

trait AssertingHelperTrait
{
    protected function verifyReady(): void
    {
        $this->assertTrue(true);
    }
}
