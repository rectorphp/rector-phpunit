<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\PHPUnit110\Rector\CallLike\AssertContainsOnlyMethodCallRector;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->rule(AssertContainsOnlyMethodCallRector::class);
};
