<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\CodeQuality\Rector\MethodCall\AssertEqualsToSameRector;
use Rector\PHPUnit\CodeQuality\Rector\MethodCall\MatchAssertSameExpectedTypeRector;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->rules([
        MatchAssertSameExpectedTypeRector::class,
        AssertEqualsToSameRector::class,
    ]);
};
