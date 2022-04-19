<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\Rector\MethodCall\WithConsecutiveArgToArrayRector;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->rule(WithConsecutiveArgToArrayRector::class);
};
