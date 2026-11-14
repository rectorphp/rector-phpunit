<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AnonThenHook extends TestCase
{
    public function testFirst()
    {
        $object = new class {
            public function run() {}
        };
        $this->assertNotNull($object);
    }

    public function testSecond()
    {
        $value = 1;
    }

    protected function tearDown(): void
    {
        $this->assertTrue(true);
    }
}
