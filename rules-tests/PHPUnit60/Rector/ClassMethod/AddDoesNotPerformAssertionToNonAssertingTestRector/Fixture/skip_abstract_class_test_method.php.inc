<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

use PHPUnit\Framework\TestCase;

abstract class SkipAbstractClassTestMethod extends TestCase
{
    // a child class can add asserting lifecycle methods
    public function testSomething()
    {
        $value = 5;
    }
}
