<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\CodeQuality\Rector\ClassMethod\BareCreateMockAssignToDirectUseRector;

return RectorConfig::configure()
    ->withRules([BareCreateMockAssignToDirectUseRector::class]);
