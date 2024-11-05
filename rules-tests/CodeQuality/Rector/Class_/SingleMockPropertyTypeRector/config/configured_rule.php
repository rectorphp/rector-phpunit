<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\CodeQuality\Rector\Class_\SingleMockPropertyTypeRector;

return RectorConfig::configure()
    ->withRules([SingleMockPropertyTypeRector::class]);
