<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\PHPUnit90\Rector\MethodCall\SpecificAssertContainsWithoutIdentityRector;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->import(\Rector\PHPUnit\Tests\ConfigList::MAIN);

    $rectorConfig->rule(SpecificAssertContainsWithoutIdentityRector::class);
};
