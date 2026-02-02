<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\CodeQuality\Rector\Expression\ConfiguredMockEntityToSetterObjectRector;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->rule(ConfiguredMockEntityToSetterObjectRector::class);
};
