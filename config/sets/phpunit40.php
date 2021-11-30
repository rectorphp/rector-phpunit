<?php

declare(strict_types=1);

use Rector\Renaming\Rector\MethodCall\RenameMethodRector;
use Rector\Renaming\ValueObject\MethodCallRename;
use Symfony\Component\DependencyInjection\Loader\Configurator\ContainerConfigurator;

return static function (ContainerConfigurator $containerConfigurator): void {
    $services = $containerConfigurator->services();

    $services->set(RenameMethodRector::class)
        ->configure([
            new MethodCallRename(
                'PHPUnit_Framework_MockObject_MockObject',
                # see https://github.com/sebastianbergmann/phpunit-mock-objects/issues/137
                'staticExpects',
                'expects'
            ),
        ]);
};
