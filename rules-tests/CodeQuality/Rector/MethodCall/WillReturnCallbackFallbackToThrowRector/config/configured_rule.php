<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\CodeQuality\Rector\MethodCall\WillReturnCallbackFallbackToThrowRector;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->rule(WillReturnCallbackFallbackToThrowRector::class);
};
