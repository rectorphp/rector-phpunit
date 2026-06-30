<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\InlineStubPropertyToCreateStubMethodCallRector\Fixture;

use PHPUnit\Framework\TestCase;
use PHPUnit\Framework\MockObject\Stub;
use Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\InlineStubPropertyToCreateStubMethodCallRector\Source\NotRelevantClass;

final class ReuseVariableOnMultipleUses extends TestCase
{
    private Stub $formatter;

    protected function setUp(): void
    {
        $this->formatter = $this->createStub(NotRelevantClass::class);
    }

    public function testAnother()
    {
        $handler = new NotRelevantClass($this->formatter);

        $this->assertSame(spl_object_id($this->formatter), spl_object_id($handler));
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\InlineStubPropertyToCreateStubMethodCallRector\Fixture;

use PHPUnit\Framework\TestCase;
use PHPUnit\Framework\MockObject\Stub;
use Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\InlineStubPropertyToCreateStubMethodCallRector\Source\NotRelevantClass;

final class ReuseVariableOnMultipleUses extends TestCase
{
    protected function setUp(): void
    {
    }

    public function testAnother()
    {
        $formatterStub = $this->createStub(\Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\InlineStubPropertyToCreateStubMethodCallRector\Source\NotRelevantClass::class);
        $handler = new NotRelevantClass($formatterStub);

        $this->assertSame(spl_object_id($formatterStub), spl_object_id($handler));
    }
}

?>
