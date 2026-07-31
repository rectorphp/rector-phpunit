<?php

namespace Rector\PHPUnit\Tests\PHPUnit110\Rector\ClassMethod\MockObjectArgCreateStubToCreateMockRector\Fixture;

use PHPUnit\Framework\MockObject\MockObject;
use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\PHPUnit110\Rector\ClassMethod\MockObjectArgCreateStubToCreateMockRector\Source\SomeUser;

final class IntersectionDocblockParam extends TestCase
{
    public function test()
    {
        $user = $this->createStub(SomeUser::class);
        $this->prepareCommonMocks('some_event', $user);
    }

    /**
     * @param MockObject&SomeUser $user
     */
    private function prepareCommonMocks(string $event, MockObject $user): void
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

final class IntersectionDocblockParam extends TestCase
{
    public function test()
    {
        $user = $this->createMock(SomeUser::class);
        $this->prepareCommonMocks('some_event', $user);
    }

    /**
     * @param MockObject&SomeUser $user
     */
    private function prepareCommonMocks(string $event, MockObject $user): void
    {
        $user->expects($this->once())
            ->method('getId')
            ->willReturn(1);
    }
}

?>
