<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\PHPUnit120\Rector\MethodCall\ExplicitMockExpectsCallRector;

return RectorConfig::configure()
    ->withRules([ExplicitMockExpectsCallRector::class]);
