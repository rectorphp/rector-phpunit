<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\AddIntersectionVarToMockObjectPropertyRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipStubPropertyTest extends TestCase
{
    private \PHPUnit\Framework\MockObject\Stub $someServiceMock;

    protected function setUp(): void
    {
        $this->someServiceMock = $this->createMock(\stdClass::class);
    }
}
