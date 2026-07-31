<?php

namespace Rector\PHPUnit\Tests\PHPUnit110\Rector\ClassMethod\ExpectsParamToMockObjectRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\PHPUnit110\Rector\ClassMethod\ExpectsParamToMockObjectRector\Source\SomeUser;

final class SkipNoExpects extends TestCase
{
    private function useUser(SomeUser $user): void
    {
        $user->getId();
    }
}
