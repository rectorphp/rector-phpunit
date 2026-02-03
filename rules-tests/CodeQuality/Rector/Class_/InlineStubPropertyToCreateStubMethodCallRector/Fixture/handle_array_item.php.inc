<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\InlineStubPropertyToCreateStubMethodCallRector\Fixture;

use PHPUnit\Framework\TestCase;
use PHPUnit\Framework\MockObject\Stub;
use Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\InlineStubPropertyToCreateStubMethodCallRector\Source\NotRelevantClass;

final class HandleArrayItem extends TestCase
{
    private Stub $someStub;

    protected function setUp(): void
    {
        $this->someStub = $this->createStub(NotRelevantClass::class);
    }

    public function testAnother()
    {
        $anotherObject = new NotRelevantClass($this->someStub);
    }

    public function testArrayItems()
    {
        $anotherObject = $this->getMockBuilder(NotRelevantClass::class)
            ->setConstructorArgs([$this->someStub]);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\InlineStubPropertyToCreateStubMethodCallRector\Fixture;

use PHPUnit\Framework\TestCase;
use PHPUnit\Framework\MockObject\Stub;
use Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\InlineStubPropertyToCreateStubMethodCallRector\Source\NotRelevantClass;

final class HandleArrayItem extends TestCase
{
    protected function setUp(): void
    {
    }

    public function testAnother()
    {
        $anotherObject = new NotRelevantClass($this->createStub(\Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\InlineStubPropertyToCreateStubMethodCallRector\Source\NotRelevantClass::class));
    }

    public function testArrayItems()
    {
        $anotherObject = $this->getMockBuilder(NotRelevantClass::class)
            ->setConstructorArgs([$this->createStub(\Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\InlineStubPropertyToCreateStubMethodCallRector\Source\NotRelevantClass::class)]);
    }
}

?>
