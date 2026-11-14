<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\ClassMethod\ExpressionCreateMockToCreateStubRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\PHPUnit120\Rector\ClassMethod\ExpressionCreateMockToCreateStubRector\Source\ClassWithDependency;

final class SkipArrayAssignedToVariable extends TestCase
{
    public function test()
    {
        $a = $this->createMock(\stdClass::class);
        $mocks = [$a];
        foreach ($mocks as $mock) {
            $mock->expects($this->once())->method('someMethod')->willReturn('someValue');
        }

        $someObject = new ClassWithDependency($a);
        $this->assertSame($a, $someObject->getDependency());
    }
}
