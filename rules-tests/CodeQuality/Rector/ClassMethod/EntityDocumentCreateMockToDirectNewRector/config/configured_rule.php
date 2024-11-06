<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\CodeQuality\Rector\ClassMethod\EntityDocumentCreateMockToDirectNewRector;

return RectorConfig::configure()
    ->withRules([EntityDocumentCreateMockToDirectNewRector::class]);
