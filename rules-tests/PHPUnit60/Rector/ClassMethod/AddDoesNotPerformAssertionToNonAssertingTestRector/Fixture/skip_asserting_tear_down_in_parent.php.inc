<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

use Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Source\AbstractClassWithAssertingTearDown;

class SkipAssertingTearDownInParent extends AbstractClassWithAssertingTearDown
{
    public function testSomething()
    {
        $value = 5;
    }
}
