<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

use PHPUnit\Framework\TestCase;

class SkipAssertingAfterAnnotation extends TestCase
{
    /**
     * @after
     */
    protected function cleanup(): void
    {
        $this->assertTrue(true);
    }

    public function testSomething()
    {
        $value = 5;
    }
}
