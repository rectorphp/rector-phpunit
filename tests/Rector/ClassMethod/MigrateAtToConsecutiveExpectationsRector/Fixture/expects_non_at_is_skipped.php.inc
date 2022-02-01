<?php

namespace Rector\PHPUnit\Tests\Rector\ClassMethod\MigrateAtToConsecutiveExpectationsRector\Fixture;

use Rector\PHPUnit\Tests\Rector\ClassMethod\MigrateAtToConsecutiveExpectationsRector\Source\SomeObject;

final class ExpectsNonAtIsSkipped extends \PHPUnit\Framework\TestCase
{
    public function test(): void
    {
        $mock = $this->createMock(SomeObject::class);
        $mock
            ->expects($this->exactly(1))
            ->method('someMethod');
    }
}

?>
