<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\CodeQuality\Rector\MethodCall\AssertThatToDirectAssertRector;

return RectorConfig::configure()
    ->withRules([AssertThatToDirectAssertRector::class]);
