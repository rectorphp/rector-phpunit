<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

use Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Source\AbstractClassUsingAssertingTrait;

final class SkipAssertingSetUpInTraitOfParent extends AbstractClassUsingAssertingTrait
{
    public function testSomething()
    {
        $value = 5;
    }
}
