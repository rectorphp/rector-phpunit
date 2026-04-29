<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\ClassMethod\ExpressionCreateMockToCreateStubRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\PHPUnit120\Rector\ClassMethod\ExpressionCreateMockToCreateStubRector\Source\ClassWithDependency;

final class SkipUsedAsNextArgMockObjectTypeNamed extends TestCase
{
    public function test()
    {
        $mock = $this->createMock(ClassWithDependency::class);
        $this->configureMock(mock: $mock, otherParam: 1);
    }

    private function configureMock($otherParam, \PHPUnit\Framework\MockObject\MockObject $mock)
    {
        $mock->method('someMethod')->willReturn(1);
    }
}
