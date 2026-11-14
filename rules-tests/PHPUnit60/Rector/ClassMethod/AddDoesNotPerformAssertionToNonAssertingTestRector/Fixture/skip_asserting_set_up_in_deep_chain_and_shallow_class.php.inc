<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

use PHPUnit\Framework\TestCase;

abstract class DeepC0 extends TestCase { protected function setUp(): void { $this->assertTrue(true); } }
abstract class DeepC1 extends DeepC0 { protected function setUp(): void { parent::setUp(); } }
abstract class DeepC2 extends DeepC1 { protected function setUp(): void { parent::setUp(); } }

final class DeepCTest extends DeepC2
{
    public function testSomething()
    {
        $value = 1;
    }
}

final class DeepCShallowTest extends DeepC1
{
    public function testOther()
    {
        $other = 2;
    }
}
