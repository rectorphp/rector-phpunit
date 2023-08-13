<?php

declare(strict_types=1);
use Rector\Config\RectorConfig;
use Rector\PHPUnit\PHPUnit100\Rector\MethodCall\PropertyExistsWithoutAssertRector;

return static function (RectorConfig $rectorConfig): void {

    $rectorConfig->rule(PropertyExistsWithoutAssertRector::class);
};
