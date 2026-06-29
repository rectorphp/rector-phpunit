<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\CodeQuality\Rector\Class_\AddIntersectionVarToMockObjectPropertyRector;

return RectorConfig::configure()
    ->withRules([AddIntersectionVarToMockObjectPropertyRector::class]);
