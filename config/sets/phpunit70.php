<?php

declare(strict_types=1);

use Rector\PHPUnit\Rector\Class_\RemoveDataProviderTestPrefixRector;
use Rector\Renaming\Rector\ClassMethod\RenameAnnotationRector;
use Rector\Renaming\ValueObject\RenameAnnotationByType;
use Symfony\Component\DependencyInjection\Loader\Configurator\ContainerConfigurator;

return static function (\Rector\Config\RectorConfig $containerConfigurator): void {
    $containerConfigurator->import(__DIR__ . '/phpunit-exception.php');

    $services = $containerConfigurator->services();

    $services->set(RenameAnnotationRector::class)
        ->configure([new RenameAnnotationByType('PHPUnit\Framework\TestCase', 'scenario', 'test')]);

    $services->set(RemoveDataProviderTestPrefixRector::class);
};
