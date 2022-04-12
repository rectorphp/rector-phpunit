<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;

use Rector\DeadCode\Rector\StaticCall\RemoveParentCallWithoutParentRector;
use Rector\PHPUnit\Rector\Class_\ConstructClassMethodToSetUpTestCaseRector;

return static function (RectorConfig $containerConfigurator): void {
    $containerConfigurator->import(__DIR__ . '/../../../../../config/config.php');

    $services = $containerConfigurator->services();

    $services->set(RemoveParentCallWithoutParentRector::class);
    $services->set(ConstructClassMethodToSetUpTestCaseRector::class);
};
