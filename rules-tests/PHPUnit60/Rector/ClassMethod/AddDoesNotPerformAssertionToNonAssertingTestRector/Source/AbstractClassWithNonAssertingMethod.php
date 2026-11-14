<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Source;

use PHPUnit\Framework\TestCase;

abstract class AbstractClassWithNonAssertingMethod extends TestCase
{
    public function testSomething()
    {
        $value = 1 + 1;
    }
}
