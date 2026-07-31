<?php

namespace Rector\PHPUnit\Tests\PHPUnit110\Rector\ClassMethod\MockObjectArgCreateStubToCreateMockRector\Fixture;

use PHPUnit\Framework\MockObject\MockObject;
use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\PHPUnit110\Rector\ClassMethod\MockObjectArgCreateStubToCreateMockRector\Source\SomeUser;

final class PassedToMockObjectParam extends TestCase
{
    public function test()
    {
        $user = $this->createStub(SomeUser::class);
        $this->prepareUserMock($user);
    }

    private function prepareUserMock(MockObject $user): void
    {
        $user->expects($this->once())
            ->method('getId')
            ->willReturn(1);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit110\Rector\ClassMethod\MockObjectArgCreateStubToCreateMockRector\Fixture;

use PHPUnit\Framework\MockObject\MockObject;
use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\PHPUnit110\Rector\ClassMethod\MockObjectArgCreateStubToCreateMockRector\Source\SomeUser;

final class PassedToMockObjectParam extends TestCase
{
    public function test()
    {
        $user = $this->createMock(SomeUser::class);
        $this->prepareUserMock($user);
    }

    private function prepareUserMock(MockObject $user): void
    {
        $user->expects($this->once())
            ->method('getId')
            ->willReturn(1);
    }
}

?>
