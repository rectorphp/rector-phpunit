<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

use PHPUnit\Framework\TestCase;

trait SetUpCallingUsingClassTrait
{
    protected function setUp(): void
    {
        $this->check();
    }
}

final class SkipSetUpCallingUsingClass extends TestCase
{
    use SetUpCallingUsingClassTrait;

    private function check(): void
    {
        $this->assertTrue(true);
    }

    public function testSomething()
    {
        $value = 1;
    }
}
