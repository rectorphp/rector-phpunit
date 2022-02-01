<?php

namespace Rector\PHPUnit\Tests\Rector\ClassMethod\MigrateAtToConsecutiveExpectationsRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\Rector\ClassMethod\MigrateAtToConsecutiveExpectationsRector\Source\SomeObject;

final class SkipDynamicVariable extends TestCase
{
    public function test(): void
    {
        $one = 1;
        $two = 2;

        $mock = $this->createMock(SomeObject::class);

        $mock
            ->expects($this->at($one))
            ->with(0)
            ->method('someMethod')
            ->willReturn('0');
        $mock
            ->expects($this->at($two))
            ->with(1)
            ->method('someMethod')
            ->willReturn('1');
    }
}
