<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\CodeQuality\Rector\ClassMethod\NoSetupWithParentCallOverrideRector;

return RectorConfig::configure()
    ->withRules([NoSetupWithParentCallOverrideRector::class]);
