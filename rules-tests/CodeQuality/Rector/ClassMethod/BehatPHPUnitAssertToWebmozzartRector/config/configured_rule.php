<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\CodeQuality\Rector\ClassMethod\BehatPHPUnitAssertToWebmozzartRector;

return RectorConfig::configure()
    ->withRules([BehatPHPUnitAssertToWebmozzartRector::class]);
