<?php

namespace Rector\PHPUnit\Tests\PHPUnit110\Rector\ClassMethod\ExpectsParamToMockObjectRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\PHPUnit110\Rector\ClassMethod\ExpectsParamToMockObjectRector\Source\SomeUser;

final class OnlyExpectsParam extends TestCase
{
    private function prepareUserMock(SomeUser $user, SomeUser $anotherUser): void
    {
        $anotherUser->getId();

        $user->expects($this->once())
            ->method('getId');
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit110\Rector\ClassMethod\ExpectsParamToMockObjectRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\PHPUnit110\Rector\ClassMethod\ExpectsParamToMockObjectRector\Source\SomeUser;

final class OnlyExpectsParam extends TestCase
{
    private function prepareUserMock(\PHPUnit\Framework\MockObject\MockObject $user, SomeUser $anotherUser): void
    {
        $anotherUser->getId();

        $user->expects($this->once())
            ->method('getId');
    }
}

?>
