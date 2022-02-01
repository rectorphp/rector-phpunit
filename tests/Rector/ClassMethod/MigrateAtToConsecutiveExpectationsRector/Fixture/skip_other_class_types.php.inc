<?php

namespace Rector\PHPUnit\Tests\Rector\ClassMethod\MigrateAtToConsecutiveExpectationsRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipOtherClassTypes extends TestCase
{
    public function testSuccessfulBuildFoundEntity($expecataiton): void
    {
        $entity = $this->createMock(TestCase::class);
        $entity->expects($expecataiton)->method('getId');
    }
}
