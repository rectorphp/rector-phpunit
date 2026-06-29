<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\AddStubIntersectionVarToStubPropertyRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipMockObjectPropertyTest extends TestCase
{
    private \PHPUnit\Framework\MockObject\MockObject $someServiceMock;

    protected function setUp(): void
    {
        $this->someServiceMock = $this->createStub(\stdClass::class);
    }
}
