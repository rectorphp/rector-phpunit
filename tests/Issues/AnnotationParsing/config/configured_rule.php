<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\DeadCode\Rector\ClassMethod\RemoveUselessReturnTagRector;
use Rector\PHPUnit\CodeQuality\Rector\Class_\YieldDataProviderRector;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->rules([YieldDataProviderRector::class, RemoveUselessReturnTagRector::class]);
};
