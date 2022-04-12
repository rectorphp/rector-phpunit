<?php

declare(strict_types=1);

use Symfony\Component\DependencyInjection\Loader\Configurator\ContainerConfigurator;

return static function (\Rector\Config\RectorConfig $containerConfigurator): void {
    $services = $containerConfigurator->services();

    $services->defaults()
        ->public()
        ->autowire()
        ->autoconfigure();

    $services->load('Rector\\PHPUnit\\', __DIR__ . '/../src')
        ->exclude([__DIR__ . '/../src/{Rector,ValueObject,PhpDoc/Node}']);
};
