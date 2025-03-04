<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\CodeQuality\Rector\MethodCall\AssertCountWithZeroToAssertEmptyRector;
use Rector\PHPUnit\CodeQuality\Rector\MethodCall\AssertEmptyNullableObjectToAssertInstanceofRector;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->rules([
        AssertCountWithZeroToAssertEmptyRector::class,
        AssertEmptyNullableObjectToAssertInstanceofRector::class,
    ]);
};
