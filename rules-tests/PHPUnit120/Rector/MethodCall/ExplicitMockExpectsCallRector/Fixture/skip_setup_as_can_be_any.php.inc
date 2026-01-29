<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\MethodCall\ExplicitMockExpectsCallRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipSetupAsCanBeAny extends TestCase
{
    protected function setUp(): void
    {
        $someClass = $this->createMock(\stdClass::class);

        $someClass->method('some');
    }
}
