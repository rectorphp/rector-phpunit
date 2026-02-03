<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\PHPUnit120\Rector\Class_\PropertyCreateMockToCreateStubRector;

return RectorConfig::configure()
    ->withRules(rules: [PropertyCreateMockToCreateStubRector::class]);
