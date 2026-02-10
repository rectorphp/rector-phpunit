<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\CodeQuality\Rector\ClassMethod\BehatPHPUnitAssertToWebmozartRector;

return RectorConfig::configure()
    ->withRules([BehatPHPUnitAssertToWebmozartRector::class]);
