<?php

namespace Rector\PHPUnit\Tests\PHPUnit110\Rector\ClassMethod\ExpectsParamToMockObjectRector\Fixture;

use PHPUnit\Framework\MockObject\MockObject;
use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\PHPUnit110\Rector\ClassMethod\ExpectsParamToMockObjectRector\Source\SomeUser;

final class SkipIntersectionParam extends TestCase
{
    private function prepareUserMock(SomeUser&MockObject $user): void
    {
        $user->expects($this->once())
            ->method('getId');
    }
}
