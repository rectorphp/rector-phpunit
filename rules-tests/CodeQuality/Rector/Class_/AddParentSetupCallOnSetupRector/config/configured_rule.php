<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\CodeQuality\Rector\Class_\AddParentSetupCallOnSetupRector;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->rule(AddParentSetupCallOnSetupRector::class);
};
