<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\Rector\Class_\StaticDataProviderClassMethodRector;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->rules([StaticDataProviderClassMethodRector::class]);
};
