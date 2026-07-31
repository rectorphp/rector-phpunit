<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\PHPUnit110\Rector\ClassMethod\MockObjectArgCreateStubToCreateMockRector;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->rule(MockObjectArgCreateStubToCreateMockRector::class);
};
