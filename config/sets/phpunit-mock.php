<?php

declare(strict_types=1);

use Rector\PHPUnit\Rector\MethodCall\UseSpecificWillMethodRector;
use Symfony\Component\DependencyInjection\Loader\Configurator\ContainerConfigurator;

return static function (\Rector\Config\RectorConfig $containerConfigurator): void {
    $services = $containerConfigurator->services();

    $services->set(UseSpecificWillMethodRector::class);
};
