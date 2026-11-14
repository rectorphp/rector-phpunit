<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

use PHPUnit\Framework\TestCase;

abstract class TraitParentAssertingBase extends TestCase
{
    protected function setUp(): void
    {
        $this->assertTrue(true);
    }
}

trait TraitParentAssertingTrait
{
    protected function setUp(): void
    {
        parent::setUp();
    }
}

final class SkipTraitParentAssertingTest extends TraitParentAssertingBase
{
    use TraitParentAssertingTrait;

    public function testSomething()
    {
        $value = 1;
    }
}
