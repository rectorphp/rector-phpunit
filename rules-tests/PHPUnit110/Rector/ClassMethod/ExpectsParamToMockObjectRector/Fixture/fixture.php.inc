<?php

namespace Rector\PHPUnit\Tests\PHPUnit110\Rector\ClassMethod\ExpectsParamToMockObjectRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\PHPUnit110\Rector\ClassMethod\ExpectsParamToMockObjectRector\Source\SomeUser;

final class ExpectsOnParam extends TestCase
{
    private function prepareUserMock(SomeUser $user): void
    {
        $user->expects($this->once())
            ->method('getId')
            ->willReturn(1);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit110\Rector\ClassMethod\ExpectsParamToMockObjectRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\PHPUnit110\Rector\ClassMethod\ExpectsParamToMockObjectRector\Source\SomeUser;

final class ExpectsOnParam extends TestCase
{
    private function prepareUserMock(\PHPUnit\Framework\MockObject\MockObject $user): void
    {
        $user->expects($this->once())
            ->method('getId')
            ->willReturn(1);
    }
}

?>
