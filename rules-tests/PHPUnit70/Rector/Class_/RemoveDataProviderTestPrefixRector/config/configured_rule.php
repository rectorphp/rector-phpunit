<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\PHPUnit70\Rector\Class_\RemoveDataProviderTestPrefixRector;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->rule(RemoveDataProviderTestPrefixRector::class);
};
