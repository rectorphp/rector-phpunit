<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\CodeQuality\Rector\Class_\AddParamTypeFromDependsRector;

return RectorConfig::configure()
    ->withRules([AddParamTypeFromDependsRector::class]);
