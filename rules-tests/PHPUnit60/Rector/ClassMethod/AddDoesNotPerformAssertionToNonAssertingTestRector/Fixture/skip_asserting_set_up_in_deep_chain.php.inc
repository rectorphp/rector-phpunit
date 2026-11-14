<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

use PHPUnit\Framework\TestCase;

abstract class Deep0 extends TestCase { protected function setUp(): void { $this->assertTrue(true); } }
abstract class Deep1 extends Deep0 { protected function setUp(): void { parent::setUp(); } }
abstract class Deep2 extends Deep1 { protected function setUp(): void { parent::setUp(); } }

final class DeepTest extends Deep2
{
    public function testSomething()
    {
        $value = 1;
    }
}
