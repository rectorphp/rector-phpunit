<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\BareCreateMockAssignToDirectUseRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\BareCreateMockAssignToDirectUseRector\Source\AnotherClass;

final class HopAroundInCall extends TestCase
{
    public function test()
    {
        $someMock = $this->createMock(AnotherClass::class);

        $anotherClass = new AnotherClass(1, 2, 3, $someMock);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\BareCreateMockAssignToDirectUseRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\BareCreateMockAssignToDirectUseRector\Source\AnotherClass;

final class HopAroundInCall extends TestCase
{
    public function test()
    {
        $anotherClass = new AnotherClass(1, 2, 3, $this->createMock(AnotherClass::class));
    }
}

?>
