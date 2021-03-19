<?php

declare(strict_types=1);

use Rector\PHPUnit\Rector\ClassMethod\MigrateAtToConsecutiveExpectationsRector;
use Symfony\Component\DependencyInjection\Loader\Configurator\ContainerConfigurator;

return static function (ContainerConfigurator $containerConfigurator): void {
    $containerConfigurator->import(__DIR__ . '/../../../../../config/config.php');

    $services = $containerConfigurator->services();

    $services->set(MigrateAtToConsecutiveExpectationsRector::class);
};
