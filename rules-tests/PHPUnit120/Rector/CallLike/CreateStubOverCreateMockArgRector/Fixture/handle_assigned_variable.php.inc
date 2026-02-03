<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\CallLike\CreateStubOverCreateMockArgRector\Fixture;

use PHPUnit\Framework\TestCase;

final class HandleAssignedVariable extends TestCase
{
    public function testThat()
    {
        $itemMock = $this->createMock(\stdClass::class);

        $items = [
            $itemMock
        ];
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\CallLike\CreateStubOverCreateMockArgRector\Fixture;

use PHPUnit\Framework\TestCase;

final class HandleAssignedVariable extends TestCase
{
    public function testThat()
    {
        $itemMock = $this->createStub(\stdClass::class);

        $items = [
            $itemMock
        ];
    }
}

?>
