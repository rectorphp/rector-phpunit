<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\Class_\PropertyCreateMockToCreateStubRector\Fixture;

use PHPUnit\Framework\TestCase;

abstract class SkipAbstractClass extends TestCase
{
    private \PHPUnit\Framework\MockObject\MockObject $someMock;

    protected function setUp(): void
    {
        $this->someMock = $this->createMock(\stdClass::class);
    }

    public function testThis()
    {
        $this->assertSame('...', $this->someMock);
    }
}
