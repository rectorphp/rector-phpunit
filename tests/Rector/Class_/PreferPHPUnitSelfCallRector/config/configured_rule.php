<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\Rector\Class_\PreferPHPUnitSelfCallRector;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->rule(PreferPHPUnitSelfCallRector::class);
};
