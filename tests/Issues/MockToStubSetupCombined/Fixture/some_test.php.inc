<?php

namespace Rector\PHPUnit\Tests\Issues\MockToStubSetupCombined\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\UseSpecificWillMethodRector\Fixture\SomeClass;
use Rector\PHPUnit\Tests\Issues\MockToStubSetupCombined\Source\MockedClass;
use Symfony\Component\DependencyInjection\Argument\RewindableGenerator;

final class SomeTest extends TestCase
{
    private \PHPUnit\Framework\MockObject\MockObject $someMock;

    protected function setUp(): void
    {
        $this->someMock = $this->createMock(MockedClass::class);

        $generator = new RewindableGenerator(fn () => yield from [
            $this->someMock,
        ], 2);
    }

    public function testSomething(): void
    {
    }

    public function testAnother(): void
    {
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\Issues\MockToStubSetupCombined\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\UseSpecificWillMethodRector\Fixture\SomeClass;
use Rector\PHPUnit\Tests\Issues\MockToStubSetupCombined\Source\MockedClass;
use Symfony\Component\DependencyInjection\Argument\RewindableGenerator;

final class SomeTest extends TestCase
{
    protected function setUp(): void
    {
        $someMock = $this->createMock(MockedClass::class);

        $generator = new RewindableGenerator(fn () => yield from [
            $someMock,
        ], 2);
    }

    public function testSomething(): void
    {
    }

    public function testAnother(): void
    {
    }
}

?>
