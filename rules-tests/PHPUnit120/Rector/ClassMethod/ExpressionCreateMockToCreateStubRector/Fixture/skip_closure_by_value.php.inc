<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\ClassMethod\ExpressionCreateMockToCreateStubRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\PHPUnit120\Rector\ClassMethod\ExpressionCreateMockToCreateStubRector\Source\ClassWithDependency;

final class SkipClosureByValue extends TestCase
{
    public function test()
    {
        $a = $this->createMock(\stdClass::class);
        $configure = function () use ($a) {
            $a->expects($this->once())->method('someMethod');
        };
        $configure();

        $someObject = new ClassWithDependency($a);
        $this->assertSame($a, $someObject->getDependency());
    }
}
