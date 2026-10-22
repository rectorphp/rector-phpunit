<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\PHPUnit70\Rector\ClassMethod\ScenarioToTestAnnotationRector;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->rule(ScenarioToTestAnnotationRector::class);
};
