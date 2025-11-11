<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\FuncCall\AssertFuncCallToPHPUnitAssertRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipInStaticMethodTest extends TestCase
{
    private static function getExceptionMessage(string $fqcn): string
    {
        $exception = new $fqcn();
        assert($exception instanceof \Exception);

        return $exception->getMessage();
    }
}

?>