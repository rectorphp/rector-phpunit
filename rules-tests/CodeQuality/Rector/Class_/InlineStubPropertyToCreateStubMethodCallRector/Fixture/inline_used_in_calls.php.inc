<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\InlineStubPropertyToCreateStubMethodCallRector\Fixture;

use PHPUnit\Framework\TestCase;
use PHPUnit\Framework\MockObject\Stub;
use Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\InlineStubPropertyToCreateStubMethodCallRector\Source\NotRelevantClass;

final class InlineUsedInCalls extends TestCase
{
    private Stub $someStub;

    protected function setUp(): void
    {
        $this->someStub = $this->createStub(NotRelevantClass::class);
    }

    public function testAnother()
    {
        $anotherObject = new NotRelevantClass($this->someStub);

        $this->runThis($this->someStub);
    }

    private function runThis($object)
    {
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\InlineStubPropertyToCreateStubMethodCallRector\Fixture;

use PHPUnit\Framework\TestCase;
use PHPUnit\Framework\MockObject\Stub;
use Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\InlineStubPropertyToCreateStubMethodCallRector\Source\NotRelevantClass;

final class InlineUsedInCalls extends TestCase
{
    protected function setUp(): void
    {
    }

    public function testAnother()
    {
        $anotherObject = new NotRelevantClass($this->createStub(\Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\InlineStubPropertyToCreateStubMethodCallRector\Source\NotRelevantClass::class));

        $this->runThis($this->createStub(\Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\InlineStubPropertyToCreateStubMethodCallRector\Source\NotRelevantClass::class));
    }

    private function runThis($object)
    {
    }
}

?>
