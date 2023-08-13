<?php

declare(strict_types=1);
use Rector\Config\RectorConfig;
use Rector\PHPUnit\PHPUnit60\Rector\MethodCall\DelegateExceptionArgumentsRector;

return static function (RectorConfig $rectorConfig): void {

    $rectorConfig->rule(DelegateExceptionArgumentsRector::class);
};
