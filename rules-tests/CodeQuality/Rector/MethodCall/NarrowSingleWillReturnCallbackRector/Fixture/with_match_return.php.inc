<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\NarrowSingleWillReturnCallbackRector\Fixture;

use PHPUnit\Framework\MockObject\MockObject;
use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\NarrowSingleWillReturnCallbackRector\Source\SomeMockedClass;

final class WithMatchReturn extends TestCase
{
    public function test()
    {
        $matcher = $this->exactly(3);

        $someMockedClass = $this->createMock(SomeMockedClass::class);

        $someMockedClass->expects($matcher)
            ->method('prepare')
            ->willReturnCallback(function (...$parameters) use ($matcher): MockObject {
                match ($matcher->getInvocationCount()) {
                    1 => self::assertEquals([
                        'some_value',
                    ], $parameters),
                };

                return match ($matcher->getInvocationCount()) {
                    1 => 4,
                };
            });
    }
}

?>
-----
<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\NarrowSingleWillReturnCallbackRector\Fixture;

use PHPUnit\Framework\MockObject\MockObject;
use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\NarrowSingleWillReturnCallbackRector\Source\SomeMockedClass;

final class WithMatchReturn extends TestCase
{
    public function test()
    {
        $matcher = $this->exactly(3);

        $someMockedClass = $this->createMock(SomeMockedClass::class);

        $someMockedClass->expects($matcher)
            ->method('prepare')
            ->with('some_value')->willReturn(4);
    }
}

?>
