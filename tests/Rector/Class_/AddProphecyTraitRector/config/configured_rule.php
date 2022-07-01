<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\Rector\Class_\AddProphecyTraitRector;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->import(__DIR__ . '/../../../../../config/config.php');

    $rectorConfig->rule(AddProphecyTraitRector::class);
};
