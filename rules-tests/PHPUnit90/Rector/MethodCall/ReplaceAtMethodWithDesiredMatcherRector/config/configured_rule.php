<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\PHPUnit90\Rector\MethodCall\ReplaceAtMethodWithDesiredMatcherRector;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->rule(ReplaceAtMethodWithDesiredMatcherRector::class);
};
