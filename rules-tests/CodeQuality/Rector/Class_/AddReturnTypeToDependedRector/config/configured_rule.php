<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\CodeQuality\Rector\Class_\AddReturnTypeToDependedRector;

return RectorConfig::configure()
    ->withRules([AddReturnTypeToDependedRector::class]);
