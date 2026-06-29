<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\CodeQuality\Rector\Class_\AddStubIntersectionVarToStubPropertyRector;

return RectorConfig::configure()
    ->withRules([AddStubIntersectionVarToStubPropertyRector::class]);
