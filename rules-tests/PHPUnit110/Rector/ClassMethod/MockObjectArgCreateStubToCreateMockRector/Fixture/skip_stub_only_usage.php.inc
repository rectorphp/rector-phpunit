<?php

namespace Rector\PHPUnit\Tests\PHPUnit110\Rector\ClassMethod\MockObjectArgCreateStubToCreateMockRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\PHPUnit110\Rector\ClassMethod\MockObjectArgCreateStubToCreateMockRector\Source\SomeUser;

final class SkipStubOnlyUsage extends TestCase
{
    public function test()
    {
        $user = $this->createStub(SomeUser::class);
        $user->method('getId')->willReturn(1);

        $this->assertSame(1, $user->getId());
    }
}
