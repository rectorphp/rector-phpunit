<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\PHPUnit120\Rector\ClassMethod\ExpressionCreateMockToCreateStubRector;

return RectorConfig::configure()
    ->withRules(rules: [ExpressionCreateMockToCreateStubRector::class]);
