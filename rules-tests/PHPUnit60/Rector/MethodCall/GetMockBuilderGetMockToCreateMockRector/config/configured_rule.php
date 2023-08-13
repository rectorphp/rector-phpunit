<?php

declare(strict_types=1);
use Rector\Config\RectorConfig;
use Rector\PHPUnit\PHPUnit60\Rector\MethodCall\GetMockBuilderGetMockToCreateMockRector;

return static function (RectorConfig $rectorConfig): void {

    $rectorConfig->rule(GetMockBuilderGetMockToCreateMockRector::class);
};
