<?php

namespace Rector\PHPUnit\Tests\PHPUnit110\Rector\ClassMethod\ExpectsParamToMockObjectRector\Fixture;

use PHPUnit\Framework\MockObject\MockObject;
use PHPUnit\Framework\TestCase;

final class SkipMockObjectParam extends TestCase
{
    private function prepareUserMock(MockObject $user): void
    {
        $user->expects($this->once())
            ->method('getId');
    }
}
