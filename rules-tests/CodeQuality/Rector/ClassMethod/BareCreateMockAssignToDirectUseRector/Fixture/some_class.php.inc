<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\BareCreateMockAssignToDirectUseRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SomeClass extends TestCase
{
    public function test()
    {
        $someMock = $this->createMock(\Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\BareCreateMockAssignToDirectUseRector\Source\AnotherClass::class);

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

final class SomeClass extends TestCase
{
    public function test()
    {
        $this->useMock($this->createMock(\Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\BareCreateMockAssignToDirectUseRector\Source\AnotherClass::class));
    }

    private function useMock($someMock)
    {
    }
}

?>
