<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\Class_\AllowMockObjectsWithoutExpectationsAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipIfMockNotUsedIn2TestMethods extends TestCase
{
    private \PHPUnit\Framework\MockObject\MockObject $someMock;

    protected function setUp(): void
    {
        $this->someMock = $this->createMock(\stdClass::class);
    }

    public function testOne()
    {
    }

    public function testTwo()
    {
    }
}
