<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

use Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Source\AbstractClassWithAssertingMethod;

class SkipParentTestCallWithAssert extends AbstractClassWithAssertingMethod
{
    public function testSomething()
    {
        parent::testSomething();
    }
}
