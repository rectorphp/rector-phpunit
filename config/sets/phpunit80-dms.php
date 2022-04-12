<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\Rector\MethodCall\ReplaceAssertArraySubsetWithDmsPolyfillRector;

return static function (RectorConfig $containerConfigurator): void {
    $services = $containerConfigurator->services();

    $services->set(ReplaceAssertArraySubsetWithDmsPolyfillRector::class);
};
