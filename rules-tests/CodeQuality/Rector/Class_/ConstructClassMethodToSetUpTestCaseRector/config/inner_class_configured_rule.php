<?php

declare(strict_types=1);
use Rector\PHPUnit\Tests\ConfigList;

use Rector\Config\RectorConfig;
use Rector\DeadCode\Rector\StaticCall\RemoveParentCallWithoutParentRector;
use Rector\PHPUnit\CodeQuality\Rector\Class_\ConstructClassMethodToSetUpTestCaseRector;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->import(ConfigList::MAIN);

    $rectorConfig->rule(RemoveParentCallWithoutParentRector::class);
    $rectorConfig->rule(ConstructClassMethodToSetUpTestCaseRector::class);
};
