<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

use PHPUnit\Framework\TestCase;

trait AssertingBeforeTrait
{
    #[\PHPUnit\Framework\Attributes\Before]
    protected function check(): void
    {
        $this->assertTrue(true);
    }
}

final class TraitBefore extends TestCase
{
    use AssertingBeforeTrait;

    public function testSomething()
    {
        $value = 1;
    }
}
