<?php

declare(strict_types=1);

use PHPUnit\Framework\TestCase;

use Rector\Config\RectorConfig;

use Rector\PHPUnit\Rector\Class_\ArrayArgumentToDataProviderRector;
use Rector\PHPUnit\ValueObject\ArrayArgumentToDataProvider;

return static function (RectorConfig $containerConfigurator): void {
    $containerConfigurator->import(__DIR__ . '/../../../../../config/config.php');

    $services = $containerConfigurator->services();

    $services->set(ArrayArgumentToDataProviderRector::class)
        ->configure([
            new ArrayArgumentToDataProvider(TestCase::class, 'doTestMultiple', 'doTestSingle', 'variable'),
        ]);
};
