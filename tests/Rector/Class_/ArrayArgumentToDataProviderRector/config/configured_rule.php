<?php

declare(strict_types=1);

use PHPUnit\Framework\TestCase;

use Rector\Config\RectorConfig;
use Rector\PHPUnit\Rector\Class_\ArrayArgumentToDataProviderRector;
use Rector\PHPUnit\ValueObject\ArrayArgumentToDataProvider;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->import(__DIR__ . '/../../../../../config/config.php');

    $rectorConfig->ruleWithConfiguration(ArrayArgumentToDataProviderRector::class, [
        new ArrayArgumentToDataProvider(TestCase::class, 'doTestMultiple', 'doTestSingle', 'variable'),
    ]);
};
