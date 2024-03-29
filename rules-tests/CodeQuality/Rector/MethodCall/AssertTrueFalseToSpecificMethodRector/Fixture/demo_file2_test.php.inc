<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertTrueFalseToSpecificMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class DemoFile2Test extends TestCase
{
    /**
     * @var object<ExceptionInterface::class> $exception
     * @dataProvider exceptionsDataProvider
     **/
    public function testExceptionIsInstanceOfExceptionInterface(object $exception): void
    {
        self::assertTrue(is_a($exception, \Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertTrueFalseToSpecificMethodRector\Fixture\ExceptionInterface::class, true));
    }

    public static function exceptionsDataProvider(): iterable
    {
        yield from [
            \Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertTrueFalseToSpecificMethodRector\Fixture\ExceptionInterface::class => [new Exception]
        ];
    }
}

interface ExceptionInterface {
}

class Exception implements \Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertTrueFalseToSpecificMethodRector\Fixture\ExceptionInterface {}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertTrueFalseToSpecificMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class DemoFile2Test extends TestCase
{
    /**
     * @var object<ExceptionInterface::class> $exception
     * @dataProvider exceptionsDataProvider
     **/
    public function testExceptionIsInstanceOfExceptionInterface(object $exception): void
    {
        self::assertInstanceOf(\Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertTrueFalseToSpecificMethodRector\Fixture\ExceptionInterface::class, $exception);
    }

    public static function exceptionsDataProvider(): iterable
    {
        yield from [
            \Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertTrueFalseToSpecificMethodRector\Fixture\ExceptionInterface::class => [new Exception]
        ];
    }
}

interface ExceptionInterface {
}

class Exception implements \Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertTrueFalseToSpecificMethodRector\Fixture\ExceptionInterface {}

?>
