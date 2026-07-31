<?php

namespace Rector\PHPUnit\Tests\PHPUnit110\Rector\ClassMethod\MockObjectArgCreateStubToCreateMockRector\Fixture;

use PHPUnit\Framework\MockObject\MockObject;
use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\PHPUnit110\Rector\ClassMethod\MockObjectArgCreateStubToCreateMockRector\Source\SomeUser;

final class NamedArg extends TestCase
{
    public function test()
    {
        $user = $this->createStub(SomeUser::class);
        $this->prepareUserMock(user: $user);
    }

    private function prepareUserMock(MockObject $user): void
    {
        $user->expects($this->once())
            ->method('getId');
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit110\Rector\ClassMethod\MockObjectArgCreateStubToCreateMockRector\Fixture;

use PHPUnit\Framework\MockObject\MockObject;
use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\PHPUnit110\Rector\ClassMethod\MockObjectArgCreateStubToCreateMockRector\Source\SomeUser;

final class NamedArg extends TestCase
{
    public function test()
    {
        $user = $this->createMock(SomeUser::class);
        $this->prepareUserMock(user: $user);
    }

    private function prepareUserMock(MockObject $user): void
    {
        $user->expects($this->once())
            ->method('getId');
    }
}

?>
