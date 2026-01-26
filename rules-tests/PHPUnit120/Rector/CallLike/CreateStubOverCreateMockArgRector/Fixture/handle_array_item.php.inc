<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\CallLike\CreateStubOverCreateMockArgRector\Fixture;

use PHPUnit\Framework\TestCase;

final class HandleArrayItem extends TestCase
{
    public function testThat()
    {
        $items = [
            $this->createMock(\stdClass::class),
        ];
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\CallLike\CreateStubOverCreateMockArgRector\Fixture;

use PHPUnit\Framework\TestCase;

final class HandleArrayItem extends TestCase
{
    public function testThat()
    {
        $items = [
            $this->createStub(\stdClass::class),
        ];
    }
}

?>
