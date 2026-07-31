<?php

namespace Rector\PHPUnit\Tests\PHPUnit110\Rector\ClassMethod\MockObjectArgCreateStubToCreateMockRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\PHPUnit110\Rector\ClassMethod\MockObjectArgCreateStubToCreateMockRector\Source\SomeUser;

final class SkipPlainParamType extends TestCase
{
    public function test()
    {
        $user = $this->createStub(SomeUser::class);
        $this->useUser($user);
    }

    private function useUser(SomeUser $user): void
    {
        $user->getId();
    }
}
