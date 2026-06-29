<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\AddStubIntersectionVarToStubPropertyRector\Fixture;

final class SkipNonTestClass
{
    private \PHPUnit\Framework\MockObject\Stub $someServiceStub;

    public function setUp(): void
    {
        $this->someServiceStub = $this->createStub(\stdClass::class);
    }
}
