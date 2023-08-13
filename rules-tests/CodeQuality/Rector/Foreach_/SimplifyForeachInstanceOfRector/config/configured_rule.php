<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\CodeQuality\Rector\Foreach_\SimplifyForeachInstanceOfRector;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->rule(SimplifyForeachInstanceOfRector::class);
};
