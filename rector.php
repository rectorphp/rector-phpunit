<?php

declare(strict_types=1);

use Rector\Core\Configuration\Option;
use Rector\Php55\Rector\String_\StringClassNameToClassConstantRector;
use Rector\Set\ValueObject\LevelSetList;
use Rector\Set\ValueObject\SetList;
use Symfony\Component\DependencyInjection\Loader\Configurator\ContainerConfigurator;

return static function (\Rector\Config\RectorConfig $containerConfigurator): void {
    $parameters = $containerConfigurator->parameters();

    $parameters->set(Option::AUTO_IMPORT_NAMES, true);
    $parameters->set(Option::PARALLEL, true);

    $parameters->set(Option::PATHS, [
        __DIR__ . '/config',
        __DIR__ . '/src',
        __DIR__ . '/tests',
    ]);
    $parameters->set(Option::SKIP, [
        // for tests
        '*/Source/*',
        '*/Fixture/*',

        // object types
        StringClassNameToClassConstantRector::class => [
            __DIR__ . '/src/Rector/MethodCall/WithConsecutiveArgToArrayRector.php',
            __DIR__ . '/src/Rector/MethodCall/UseSpecificWillMethodRector.php',
            __DIR__ . '/src/Rector/Class_/TestListenerToHooksRector.php',
            __DIR__ . '/src/NodeFactory/ConsecutiveAssertionFactory.php',
            __DIR__ . '/src/NodeAnalyzer/TestsNodeAnalyzer.php',
            __DIR__ . '/src/NodeFactory/DataProviderClassMethodFactory.php'
        ],
    ]);

    // needed for DEAD_CODE list, just in split package like this
    $containerConfigurator->import(__DIR__ . '/config/config.php');

    $containerConfigurator->import(LevelSetList::UP_TO_PHP_81);
    $containerConfigurator->import(SetList::DEAD_CODE);
    $containerConfigurator->import(SetList::CODE_QUALITY);
    $containerConfigurator->import(SetList::CODING_STYLE);
    $containerConfigurator->import(SetList::EARLY_RETURN);

    $services = $containerConfigurator->services();

    $services->set(StringClassNameToClassConstantRector::class)
        ->configure([
            // keep unprefixed to protected from downgrade
            'PHPUnit\Framework\Assert',
            'PHPUnit\Framework\MockObject\*',
            'PHPUnit\Framework\TestCase',
            'Prophecy\Prophet',
        ]);
};

