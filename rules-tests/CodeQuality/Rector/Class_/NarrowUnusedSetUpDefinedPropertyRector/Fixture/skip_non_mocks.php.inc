<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\NarrowUnusedSetUpDefinedPropertyRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\NarrowUnusedSetUpDefinedPropertyRector\Source\SomeType;

final class SkipNonMocks extends TestCase
{
    private SomeType $someMock;
    private SomeType $anotherMock;

    protected function setUp(): void
    {
        $this->someMock = new SomeType();
        $this->anotherMock = new SomeType();
    }

    public function test()
    {
        $this->anotherMock->expects($this->once());
    }
}
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\NarrowUnusedSetUpDefinedPropertyRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\NarrowUnusedSetUpDefinedPropertyRector\Source\SomeType;

final class SkipNonMocks extends TestCase
{
    private SomeType $anotherMock;

    protected function setUp(): void
    {
        $someMock = new SomeType();
        $this->anotherMock = new SomeType();
    }

    public function test()
    {
        $this->anotherMock->expects($this->once());
    }
}
