<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\CodeQuality\Rector\FuncCall\AssertFuncCallToPHPUnitAssertRector;

return RectorConfig::configure()
    ->withRules([AssertFuncCallToPHPUnitAssertRector::class]);
