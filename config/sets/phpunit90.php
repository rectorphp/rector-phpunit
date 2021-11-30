<?php

declare(strict_types=1);

use Rector\PHPUnit\Rector\Class_\TestListenerToHooksRector;
use Rector\PHPUnit\Rector\MethodCall\ExplicitPhpErrorApiRector;
use Rector\PHPUnit\Rector\MethodCall\SpecificAssertContainsWithoutIdentityRector;
use Rector\Renaming\Rector\MethodCall\RenameMethodRector;
use Rector\Renaming\ValueObject\MethodCallRename;
use Symfony\Component\DependencyInjection\Loader\Configurator\ContainerConfigurator;

return static function (ContainerConfigurator $containerConfigurator): void {
    $services = $containerConfigurator->services();

    $services->set(TestListenerToHooksRector::class);

    $services->set(ExplicitPhpErrorApiRector::class);

    $services->set(SpecificAssertContainsWithoutIdentityRector::class);

    $services->set(RenameMethodRector::class)
        ->configure([
            // see https://github.com/sebastianbergmann/phpunit/issues/3957
            new MethodCallRename(
                'PHPUnit\Framework\TestCase',
                'expectExceptionMessageRegExp',
                'expectExceptionMessageMatches'
            ),
        ]);
};
