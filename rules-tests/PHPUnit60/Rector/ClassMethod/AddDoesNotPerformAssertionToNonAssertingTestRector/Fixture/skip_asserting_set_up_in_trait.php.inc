<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

use PHPUnit\Framework\TestCase;

trait AssertingSetUpTrait
{
    protected function setUp(): void
    {
        $this->assertTrue(true);
    }
}

final class TraitSetUp extends TestCase
{
    use AssertingSetUpTrait;

    public function testSomething()
    {
        $value = 1;
    }
}
