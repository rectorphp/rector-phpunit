<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\CallLike\CreateStubOverCreateMockArgRector\Fixture;

use PHPUnit\Framework\TestCase;
use Utils\PHPStan\Tests\Rule\PHPUnit\StubOverMockArgRule\Source\AnyClass;

class HandleStaticCall extends TestCase
{
    public function testThat()
    {
        AnyClass::staticRun(
            $this->createMock(\stdClass::class),
        );
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\CallLike\CreateStubOverCreateMockArgRector\Fixture;

use PHPUnit\Framework\TestCase;
use Utils\PHPStan\Tests\Rule\PHPUnit\StubOverMockArgRule\Source\AnyClass;

class HandleStaticCall extends TestCase
{
    public function testThat()
    {
        AnyClass::staticRun(
            $this->createStub(\stdClass::class),
        );
    }
}

?>
