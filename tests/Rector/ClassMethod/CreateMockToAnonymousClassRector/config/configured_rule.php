<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\Rector\ClassMethod\CreateMockToAnonymousClassRector;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->rule(CreateMockToAnonymousClassRector::class);
};
