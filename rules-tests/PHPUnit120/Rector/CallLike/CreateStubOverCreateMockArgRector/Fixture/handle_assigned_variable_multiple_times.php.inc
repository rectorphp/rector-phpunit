<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\CallLike\CreateStubOverCreateMockArgRector\Fixture;

use PHPUnit\Framework\TestCase;

final class HandleAssignedVariableMultipleTimes extends TestCase
{
    public function testThat()
    {
        $itemMock = $this->createMock(\stdClass::class);

        $items = [
            $itemMock
        ];

        $anotherValue = new \stdClass($itemMock);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\CallLike\CreateStubOverCreateMockArgRector\Fixture;

use PHPUnit\Framework\TestCase;

final class HandleAssignedVariableMultipleTimes extends TestCase
{
    public function testThat()
    {
        $itemMock = $this->createStub(\stdClass::class);

        $items = [
            $itemMock
        ];

        $anotherValue = new \stdClass($itemMock);
    }
}

?>
