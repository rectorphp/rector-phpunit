<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\MethodCall\ExplicitMockExpectsCallRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipPropertyAsCanBeDefinedMultipleTimes extends TestCase
{

    private \PHPUnit\Framework\MockObject\MockObject $someClass;

    protected function setUp(): void
    {
        $this->someClass = $this->createMock(\stdClass::class);
    }

    public function test(): void
    {
        $this->someClass->method('some');
    }
}
