<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\ClassMethod\ExpressionCreateMockToCreateStubRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\PHPUnit120\Rector\ClassMethod\ExpressionCreateMockToCreateStubRector\Source\ClassWithDependency;

final class SkipPropertyForExternalScope extends TestCase
{
    private \PHPUnit\Framework\MockObject\MockObject $mock;

    public function test()
    {
        $this->mock = $this->createMock(\stdClass::class);

        $someObject = new ClassWithDependency($this->mock);
        $this->assertSame($this->mock, $someObject->getDependency());
    }
}
