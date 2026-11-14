<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Source\TraitWithAssertingSetUp;

final class SkipAssertingSetUpInTraitFromOtherFile extends TestCase
{
    use TraitWithAssertingSetUp;

    public function testSomething()
    {
        $value = 5;
    }
}
