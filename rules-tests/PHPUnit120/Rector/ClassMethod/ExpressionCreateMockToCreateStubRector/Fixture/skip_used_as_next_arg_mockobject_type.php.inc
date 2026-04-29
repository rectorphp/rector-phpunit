<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\ClassMethod\ExpressionCreateMockToCreateStubRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\PHPUnit120\Rector\ClassMethod\ExpressionCreateMockToCreateStubRector\Source\ClassWithDependency;

final class SkipUsedAsNextArgMockObjectType extends TestCase
{
    public function test()
    {
        $mock = $this->createMock(ClassWithDependency::class);
        $this->configureMock($mock);
    }

    private function configureMock(\PHPUnit\Framework\MockObject\MockObject $mock)
    {
        $mock->method('someMethod')->willReturn(1);
    }
}
