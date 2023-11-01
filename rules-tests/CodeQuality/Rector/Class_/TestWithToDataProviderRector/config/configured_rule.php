<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\CodeQuality\Rector\Class_\TestWithToDataProviderRector;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->rule(TestWithToDataProviderRector::class);
};
