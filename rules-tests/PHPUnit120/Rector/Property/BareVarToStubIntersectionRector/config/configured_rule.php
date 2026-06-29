<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\PHPUnit120\Rector\Property\BareVarToStubIntersectionRector;

return RectorConfig::configure()
    ->withRules(rules: [BareVarToStubIntersectionRector::class]);
