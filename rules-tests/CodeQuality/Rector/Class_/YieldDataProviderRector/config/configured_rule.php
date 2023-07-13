<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\CodeQuality\Rector\Class_\YieldDataProviderRector;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->import(\Rector\PHPUnit\Tests\ConfigList::MAIN);

    $rectorConfig->rule(YieldDataProviderRector::class);
};
