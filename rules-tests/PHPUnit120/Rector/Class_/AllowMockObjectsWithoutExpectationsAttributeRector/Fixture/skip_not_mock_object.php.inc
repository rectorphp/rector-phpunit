<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\Class_\AllowMockObjectsWithoutExpectationsAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\PHPUnit120\Rector\Class_\AllowMockObjectsWithoutExpectationsAttributeRector\Source\ClassToStub;

final class SkipNotMockObject extends TestCase
{
    private ClassToStub $foo;

    public function setUp(): void
    {
        parent::setUp();

        $foo = self::createStub(ClassToStub::class);
        $foo->method('foo')->willReturn('error');

        $this->foo = $foo;
    }

    public function test()
    {
       $this->foo->foo();
    }
}