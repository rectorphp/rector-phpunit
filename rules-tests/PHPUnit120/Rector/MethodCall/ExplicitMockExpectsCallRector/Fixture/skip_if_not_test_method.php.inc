<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\MethodCall\ExplicitMockExpectsCallRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipIfNotTestMethod extends TestCase
{
    private function decorateMock(): void
    {
        $someClass = $this->createMock(\stdClass::class);

        $someClass->method('some');
    }
}
