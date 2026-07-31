<?php

namespace Rector\PHPUnit\Tests\PHPUnit110\Rector\ClassMethod\ExpectsParamToMockObjectRector\Fixture;

use Rector\PHPUnit\Tests\PHPUnit110\Rector\ClassMethod\ExpectsParamToMockObjectRector\Source\SomeUser;

final class SkipNonTestClass
{
    private function prepareUserMock(SomeUser $user): void
    {
        $user->expects($this->once())
            ->method('getId');
    }
}
