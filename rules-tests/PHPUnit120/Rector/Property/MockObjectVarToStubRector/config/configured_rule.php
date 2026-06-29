<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\PHPUnit120\Rector\Property\MockObjectVarToStubRector;

return RectorConfig::configure()
    ->withRules(rules: [MockObjectVarToStubRector::class]);
