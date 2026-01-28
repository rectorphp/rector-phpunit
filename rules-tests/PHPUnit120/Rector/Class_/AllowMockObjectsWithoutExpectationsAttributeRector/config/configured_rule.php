<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\PHPUnit120\Rector\Class_\AllowMockObjectsWithoutExpectationsAttributeRector;

return RectorConfig::configure()
    ->withRules([AllowMockObjectsWithoutExpectationsAttributeRector::class]);
