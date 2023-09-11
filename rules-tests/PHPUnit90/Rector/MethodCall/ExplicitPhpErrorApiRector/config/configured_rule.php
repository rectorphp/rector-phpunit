<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\PHPUnit90\Rector\MethodCall\ExplicitPhpErrorApiRector;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->rule(ExplicitPhpErrorApiRector::class);
};
