<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

trait SomeNonAssertingTrait
{
    public function testSomething()
    {
        $nothing = 5;
    }
}
