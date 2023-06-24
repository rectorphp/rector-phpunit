<?php

namespace Rector\Tests\PHPUnit\Rector\MethodCall\AssertTrueFalseToSpecificMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class DemoFileTest extends TestCase
{
    /**
     * @var class-string<ExceptionInterface::class> $exception
     * @dataProvider exceptionsDataProvider
     **/
    public function testExceptionIsInstanceOfExceptionInterface(string $exception): void
    {
        self::assertTrue(is_a($exception, ExceptionInterface::class, true));
    }
    
    public static function exceptionsDataProvider(): iterable
    {
        yield from [
            ExceptionInterface::class => [ExceptionInterface::class]
        ];
    }
}

interface ExceptionInterface {
}

?>
-----