<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\Set\PHPUnitSetList;

return static function (RectorConfig $containerConfigurator): void {
    $containerConfigurator->import(PHPUnitSetList::PHPUNIT_50);
};
