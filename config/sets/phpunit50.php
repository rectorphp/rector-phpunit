<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\Rector\StaticCall\GetMockRector;

return static function (RectorConfig $containerConfigurator): void {
    $services = $containerConfigurator->services();

    $services->set(GetMockRector::class);
};
