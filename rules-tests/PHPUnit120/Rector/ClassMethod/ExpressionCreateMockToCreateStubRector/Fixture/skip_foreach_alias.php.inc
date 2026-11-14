<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\ClassMethod\ExpressionCreateMockToCreateStubRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\PHPUnit120\Rector\ClassMethod\ExpressionCreateMockToCreateStubRector\Source\ClassWithDependency;

final class SkipForeachAlias extends TestCase
{
    public function test()
    {
        $a = $this->createMock(\stdClass::class);
        $b = $this->createMock(\stdClass::class);
        foreach ([$a, $b] as $mock) {
            $mock->expects($this->once())->method('someMethod')->willReturn('someValue');
        }

        $someObject = new ClassWithDependency($a);
        $this->assertSame($a, $someObject->getDependency());
    }
}
