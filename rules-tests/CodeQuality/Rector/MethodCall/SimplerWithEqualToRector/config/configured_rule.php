<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\CodeQuality\Rector\MethodCall\SimplerWithEqualToRector;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->rule(SimplerWithEqualToRector::class);
};
