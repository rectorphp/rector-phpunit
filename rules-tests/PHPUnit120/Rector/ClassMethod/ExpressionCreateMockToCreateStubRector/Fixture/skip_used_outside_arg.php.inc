<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\ClassMethod\ExpressionCreateMockToCreateStubRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\PHPUnit120\Rector\ClassMethod\ExpressionCreateMockToCreateStubRector\Source\ClassWithDependency;

final class SkipUsedOutsideArg extends TestCase
{
    public function test()
    {
        $mock = $this->createMock(\stdClass::class);

        if ($mock instanceof \stdClass) {
            // do something
        }

        $someObject = new ClassWithDependency($mock);
        $this->assertSame($mock, $someObject->getDependency());
    }
}
