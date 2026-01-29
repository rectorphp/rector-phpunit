<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\MethodCall\ExplicitMockExpectsCallRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipAlreadyFilled extends TestCase
{
    public function testMethod(): void
    {
        $someClass = $this->createMock(\stdClass::class);

        $someClass->expects($this->once())->method('some');
    }
}
