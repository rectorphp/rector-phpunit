<?php

namespace Rector\PHPUnit\Tests\Rector\ClassMethod\MigrateAtToConsecutiveExpectationsRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipStaticCallSelf extends TestCase
{

    public function testSuccessfulBuildFoundEntity(): void
    {
        $entity = $this->createMock(TestCase::class);
        $entity->expects(self::once())->method('getId')->willReturn(1);
    }
}
