<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\Class_\AllowMockObjectsWithoutExpectationsAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipIfAllTestsMethodsDefineExpectations extends TestCase
{
    private \PHPUnit\Framework\MockObject\MockObject $someMock;

    protected function setUp(): void
    {
        $this->someMock = $this->createMock(\stdClass::class);
    }

    public function testOne()
    {
        $this->someMock->method('doSomething')->willReturn('value');
    }

    public function testTwo()
    {
        $this->someMock->method('doSomethingElse')->willReturn('another value');
    }
}
