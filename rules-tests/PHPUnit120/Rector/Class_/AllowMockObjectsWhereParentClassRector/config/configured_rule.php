<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\PHPUnit120\Rector\Class_\AllowMockObjectsWhereParentClassRector;

return RectorConfig::configure()
    ->withRules([AllowMockObjectsWhereParentClassRector::class]);
