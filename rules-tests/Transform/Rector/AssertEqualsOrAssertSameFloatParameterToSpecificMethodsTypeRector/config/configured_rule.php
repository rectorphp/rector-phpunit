<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\Transform\AssertEqualsOrAssertSameFloatParameterToSpecificMethodsTypeRector;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->rule(AssertEqualsOrAssertSameFloatParameterToSpecificMethodsTypeRector::class);
};
