<?php

namespace Rector\Tests\PHPUnit\Rector\MethodCall\AssertTrueFalseToSpecificMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class DemoFile2Test extends TestCase
{
    /**
     * @var object<ExceptionInterface::class> $exception
     * @dataProvider exceptionsDataProvider
     **/
    public function testExceptionIsInstanceOfExceptionInterface(object $exception): void
    {
        self::assertTrue(is_a($exception, ExceptionInterface::class, true));
    }
    
    public static function exceptionsDataProvider(): iterable
    {
        yield from [
            ExceptionInterface::class => [new Exception]
        ];
    }
}

interface ExceptionInterface {
}

class Exception implements ExceptionInterface {}

?>
-----
<?php

namespace Rector\Tests\PHPUnit\Rector\MethodCall\AssertTrueFalseToSpecificMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class DemoFile2Test extends TestCase
{
    /**
     * @var object<ExceptionInterface::class> $exception
     * @dataProvider exceptionsDataProvider
     **/
    public function testExceptionIsInstanceOfExceptionInterface(object $exception): void
    {
        self::assertInstanceOf(ExceptionInterface::class, $exception);
    }
    
    public static function exceptionsDataProvider(): iterable
    {
        yield from [
            ExceptionInterface::class => [new Exception]
        ];
    }
}

interface ExceptionInterface {
}

class Exception implements ExceptionInterface {}

?>