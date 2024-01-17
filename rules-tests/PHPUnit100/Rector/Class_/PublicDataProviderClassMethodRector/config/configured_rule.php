<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\PHPUnit100\Rector\Class_\PublicDataProviderClassMethodRector;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->rule(PublicDataProviderClassMethodRector::class);
};
