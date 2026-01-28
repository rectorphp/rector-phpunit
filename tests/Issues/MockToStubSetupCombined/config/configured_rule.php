<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\CodeQuality\Rector\Class_\NarrowUnusedSetUpDefinedPropertyRector;
use Rector\PHPUnit\CodeQuality\Rector\ClassMethod\BareCreateMockAssignToDirectUseRector;

return RectorConfig::configure()
    ->withRules(rules: [
        NarrowUnusedSetUpDefinedPropertyRector::class,
        BareCreateMockAssignToDirectUseRector::class,
    ]);
