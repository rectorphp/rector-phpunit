<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;

use Rector\PHPUnit\Rector\MethodCall\AssertSameTrueFalseToAssertTrueFalseRector;

return static function (RectorConfig $containerConfigurator): void {
    $containerConfigurator->import(__DIR__ . '/../../../../../config/config.php');

    $services = $containerConfigurator->services();

    $services->set(AssertSameTrueFalseToAssertTrueFalseRector::class);
};
