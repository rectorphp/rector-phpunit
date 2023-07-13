<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\CodeQuality\Rector\MethodCall\AssertSameTrueFalseToAssertTrueFalseRector;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->import(\Rector\PHPUnit\Tests\ConfigList::MAIN);

    $rectorConfig->rule(AssertSameTrueFalseToAssertTrueFalseRector::class);
};
