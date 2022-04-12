<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;

return static function (RectorConfig $containerConfigurator): void {
    $services = $containerConfigurator->services();

    $services->defaults()
        ->public()
        ->autowire()
        ->autoconfigure();

    $services->load('Rector\\PHPUnit\\', __DIR__ . '/../src')
        ->exclude([__DIR__ . '/../src/{Rector,ValueObject,PhpDoc/Node}']);
};
