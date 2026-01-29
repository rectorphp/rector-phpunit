<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\BareCreateMockAssignToDirectUseRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\BareCreateMockAssignToDirectUseRector\Source\SomeInterfaceToBeMocked;

final class CoverInterface extends TestCase
{
    public function test()
    {
        $someMock = $this->createMock(SomeInterfaceToBeMocked::class);

        $this->useMock($someMock);
    }

    private function useMock($someMock)
    {
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\BareCreateMockAssignToDirectUseRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\BareCreateMockAssignToDirectUseRector\Source\SomeInterfaceToBeMocked;

final class CoverInterface extends TestCase
{
    public function test()
    {
        $this->useMock($this->createMock(SomeInterfaceToBeMocked::class));
    }

    private function useMock($someMock)
    {
    }
}

?>
