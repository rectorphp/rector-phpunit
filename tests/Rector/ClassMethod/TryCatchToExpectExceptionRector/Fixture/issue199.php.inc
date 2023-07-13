<?php

namespace Rector\PHPUnit\Tests\Rector\ClassMethod\TryCatchToExpectExceptionRector\Fixture;

use PHPUnit\Framework\TestCase;
use RuntimeException;

final class DemoFileTest extends TestCase
{
    public function testThrowsBadMethodCallException(): void
    {
        try {
            throw new BadMethodCallException();
        } catch (BadMethodCallException $badMethodCallException) {
            self::assertSame($badMethodCallException::class, BadMethodCallException::class);
            return;
        }

        self::fail('Exception was not thrown');
    }
}

final class BadMethodCallException extends RuntimeException
{
}

?>
-----
