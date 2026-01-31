<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\ClassMethod\ExpressionCreateMockToCreateStubRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\PHPUnit120\Rector\ClassMethod\ExpressionCreateMockToCreateStubRector\Source\ClassWithDependency;

final class SkipMocking extends TestCase
{
    public function test()
    {
        $mock = $this->createMock(\stdClass::class);
        $mock->expects($this->once())->method('someMethod')->willReturn('someValue');

        $someObject = new ClassWithDependency($mock);
        $this->assertSame($mock, $someObject->getDependency());
    }
}
