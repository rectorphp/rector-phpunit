<?php

declare(strict_types=1);
use Rector\PHPUnit\Tests\ConfigList;

use Rector\Config\RectorConfig;

use Rector\PHPUnit\PHPUnit100\Rector\Class_\StaticDataProviderClassMethodRector;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->import(ConfigList::MAIN);

    $rectorConfig->rule(StaticDataProviderClassMethodRector::class);
};
