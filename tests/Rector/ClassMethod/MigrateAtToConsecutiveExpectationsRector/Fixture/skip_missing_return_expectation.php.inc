<?php

namespace Rector\PHPUnit\Tests\Rector\ClassMethod\MigrateAtToConsecutiveExpectationsRector\Fixture;

use Rector\PHPUnit\Tests\Rector\ClassMethod\MigrateAtToConsecutiveExpectationsRector\Source\SomeObject;

final class SkipMissingReturnExpectation extends \PHPUnit\Framework\TestCase
{
    public function test(): void
    {
        $mock = $this->createMock(SomeObject::class);
        $mock
            ->expects($this->at(0))
            ->method('someMethod')
            ->willReturn('1');

        $mock
            ->expects($this->at(1))
            ->method('someMethod');

        $mock
            ->expects($this->at(2))
            ->method('someMethod')
            ->willReturn('3');
    }
}

?>
