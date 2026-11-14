<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

use Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Source\AbstractClassWithTraitAssertingSetUp;

class SkipAssertingSetUpViaParentTrait extends AbstractClassWithTraitAssertingSetUp
{
    public function testSomething()
    {
        $value = 5;
    }
}
