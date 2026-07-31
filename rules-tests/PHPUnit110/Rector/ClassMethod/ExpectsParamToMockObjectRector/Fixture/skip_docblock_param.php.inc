<?php

namespace Rector\PHPUnit\Tests\PHPUnit110\Rector\ClassMethod\ExpectsParamToMockObjectRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\PHPUnit110\Rector\ClassMethod\ExpectsParamToMockObjectRector\Source\SomeUser;

final class SkipDocblockParam extends TestCase
{
    /**
     * @param SomeUser $user
     */
    private function prepareUserMock(SomeUser $user): void
    {
        $user->expects($this->once())
            ->method('getId');
    }
}
