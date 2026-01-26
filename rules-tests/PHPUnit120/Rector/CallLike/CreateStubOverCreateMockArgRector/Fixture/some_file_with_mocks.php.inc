<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\CallLike\CreateStubOverCreateMockArgRector\Fixture;

use PHPUnit\Framework\TestCase;
use Utils\PHPStan\Tests\Rule\PHPUnit\StubOverMockArgRule\Source\AnyClass;

class SomeFileWithMocks extends TestCase
{
    public function testThat()
    {
        $anyClass = new AnyClass();
        $anyClass->run(
            $this->createMock(\stdClass::class),
            $this->createMock(\stdClass::class)
        );
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\CallLike\CreateStubOverCreateMockArgRector\Fixture;

use PHPUnit\Framework\TestCase;
use Utils\PHPStan\Tests\Rule\PHPUnit\StubOverMockArgRule\Source\AnyClass;

class SomeFileWithMocks extends TestCase
{
    public function testThat()
    {
        $anyClass = new AnyClass();
        $anyClass->run(
            $this->createStub(\stdClass::class),
            $this->createStub(\stdClass::class)
        );
    }
}

?>
