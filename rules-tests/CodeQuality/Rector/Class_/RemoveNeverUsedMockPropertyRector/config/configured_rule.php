<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\CodeQuality\Rector\Class_\RemoveNeverUsedMockPropertyRector;

return RectorConfig::configure()
    ->withRules([RemoveNeverUsedMockPropertyRector::class]);
