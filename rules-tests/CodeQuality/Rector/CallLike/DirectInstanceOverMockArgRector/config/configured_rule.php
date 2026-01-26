<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\CodeQuality\Rector\CallLike\DirectInstanceOverMockArgRector;

return RectorConfig::configure()
    ->withRules([DirectInstanceOverMockArgRector::class]);
