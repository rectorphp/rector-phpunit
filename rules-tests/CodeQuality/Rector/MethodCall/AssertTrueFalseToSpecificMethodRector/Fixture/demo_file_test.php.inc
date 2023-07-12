<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertTrueFalseToSpecificMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class DemoFileTest extends TestCase
{
    /**
     * @var class-string<\Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertTrueFalseToSpecificMethodRector\Fixture\ExceptionInterface::class> $exception
     * @dataProvider exceptionsDataProvider
     **/
    public function testExceptionIsInstanceOfExceptionInterface(string $exception): void
    {
        self::assertTrue(is_a($exception, \Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertTrueFalseToSpecificMethodRector\Fixture\ExceptionInterface::class, true));
    }

    public static function exceptionsDataProvider(): iterable
    {
        yield from [
            \Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertTrueFalseToSpecificMethodRector\Fixture\ExceptionInterface::class => [\Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertTrueFalseToSpecificMethodRector\Fixture\ExceptionInterface::class]
        ];
    }
}

interface ExceptionInterface {
}

?>
