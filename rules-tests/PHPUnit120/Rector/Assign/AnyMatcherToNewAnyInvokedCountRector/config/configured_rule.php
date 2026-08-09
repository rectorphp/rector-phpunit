<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\PHPUnit120\Rector\Assign\AnyMatcherToNewAnyInvokedCountRector;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->rule(AnyMatcherToNewAnyInvokedCountRector::class);
};
