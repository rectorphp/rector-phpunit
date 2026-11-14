<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

use PHPUnit\Framework\TestCase;

abstract class AbstractBase extends TestCase
{
    public function testInherited()
    {
        $value = 1;
    }
}

final class AbstractChild extends AbstractBase
{
    protected function setUp(): void
    {
        $this->assertTrue(true);
    }
}
