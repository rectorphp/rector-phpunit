<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\Class_\PropertyCreateMockToCreateStubRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipPropertyUsedInClosure extends TestCase
{
    private \PHPUnit\Framework\MockObject\MockObject $someMock;

    protected function setUp(): void
    {
        $this->someMock = $this->createMock(\stdClass::class);
    }

    public function testThis()
    {
        $builder = $this->createMock(\stdClass::class);
        $builder->method('addEventListener')->willReturnCallback(function () {
            $this->someMock->expects($this->once())->method('something');
        });
    }
}
