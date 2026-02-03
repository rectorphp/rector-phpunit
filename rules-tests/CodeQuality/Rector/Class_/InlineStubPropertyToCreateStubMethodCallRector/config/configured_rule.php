<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\CodeQuality\Rector\Class_\InlineStubPropertyToCreateStubMethodCallRector;

return RectorConfig::configure()
    ->withRules([InlineStubPropertyToCreateStubMethodCallRector::class]);
