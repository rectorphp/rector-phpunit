<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\PHPUnit120\Rector\CallLike\CreateStubInCoalesceArgRector;

return RectorConfig::configure()
    ->withRules([CreateStubInCoalesceArgRector::class]);
