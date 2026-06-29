<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\AddStubIntersectionVarToStubPropertyRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SomeTest extends TestCase
{
    private \PHPUnit\Framework\MockObject\Stub $someServiceStub;

    protected function setUp(): void
    {
        $this->someServiceStub = $this->createStub(\stdClass::class);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\AddStubIntersectionVarToStubPropertyRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SomeTest extends TestCase
{
    /**
     * @var \PHPUnit\Framework\MockObject\Stub&\stdClass
     */
    private \PHPUnit\Framework\MockObject\Stub $someServiceStub;

    protected function setUp(): void
    {
        $this->someServiceStub = $this->createStub(\stdClass::class);
    }
}

?>
