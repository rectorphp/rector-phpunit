<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\CodeQuality\Rector\MethodCall\MatchAssertEqualsExpectedTypeRector;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->rule(MatchAssertEqualsExpectedTypeRector::class);
};
