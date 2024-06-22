<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\PHPUnit100\Rector\MethodCall\AssertIssetToAssertObjectHasPropertyRector;

return RectorConfig::configure()
    ->withRules([AssertIssetToAssertObjectHasPropertyRector::class]);
