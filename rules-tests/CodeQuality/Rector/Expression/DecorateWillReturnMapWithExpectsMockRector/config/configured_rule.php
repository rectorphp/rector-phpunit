<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\CodeQuality\Rector\Expression\DecorateWillReturnMapWithExpectsMockRector;

return RectorConfig::configure()
    ->withRules([DecorateWillReturnMapWithExpectsMockRector::class]);
