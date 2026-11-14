<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SetUpHelper extends TestCase
{
    protected function setUp(): void
    {
        parent::setUp();
        $this->init();
    }

    private function init(): void
    {
        self::assertSame(1, 1);
    }

    public function testSomething()
    {
        $value = 1;
    }
}
