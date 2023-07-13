<?php

declare(strict_types=1);
use Rector\PHPUnit\Tests\ConfigList;

use Rector\Config\RectorConfig;
use Rector\PHPUnit\PHPUnit80\Rector\MethodCall\SpecificAssertContainsRector;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->import(ConfigList::MAIN);

    $rectorConfig->rule(SpecificAssertContainsRector::class);
};
