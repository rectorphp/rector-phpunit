<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Source;

use PHPUnit\Framework\TestCase;

abstract class AbstractClassWithTraitAssertingSetUp extends TestCase
{
    use AssertingHelperTrait;

    protected function setUp(): void
    {
        $this->verifyReady();
    }
}
