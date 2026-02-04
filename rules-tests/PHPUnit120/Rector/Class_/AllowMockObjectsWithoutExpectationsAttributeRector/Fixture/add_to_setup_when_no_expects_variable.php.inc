<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\Class_\AllowMockObjectsWithoutExpectationsAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AddToSetupWhenNoExpectsVariable extends TestCase
{
    protected function setUp(): void
    {
        $someMock = $this->createMock(\stdClass::class);
        $someMock->method('some')->willReturn(true);
    }

    public function testOne()
    {
    }

    public function testTwo()
    {
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\Class_\AllowMockObjectsWithoutExpectationsAttributeRector\Fixture;

use PHPUnit\Framework\TestCase;

#[\PHPUnit\Framework\Attributes\AllowMockObjectsWithoutExpectations]
final class AddToSetupWhenNoExpectsVariable extends TestCase
{
    protected function setUp(): void
    {
        $someMock = $this->createMock(\stdClass::class);
        $someMock->method('some')->willReturn(true);
    }

    public function testOne()
    {
    }

    public function testTwo()
    {
    }
}

?>
