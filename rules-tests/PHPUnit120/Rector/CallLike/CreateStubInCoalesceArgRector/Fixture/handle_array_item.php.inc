<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\CallLike\CreateStubInCoalesceArgRector\Fixture;

use PHPUnit\Framework\TestCase;

final class HandleArrayItem extends TestCase
{
    public function testThat()
    {
        $value = mt_rand(0, 1);

        $items = [
            $value ?? $this->createMock(\stdClass::class),
            $value ?? $this->createMock(\stdClass::class),
        ];
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\CallLike\CreateStubInCoalesceArgRector\Fixture;

use PHPUnit\Framework\TestCase;

final class HandleArrayItem extends TestCase
{
    public function testThat()
    {
        $value = mt_rand(0, 1);

        $items = [
            $value ?? $this->createStub(\stdClass::class),
            $value ?? $this->createStub(\stdClass::class),
        ];
    }
}

?>
