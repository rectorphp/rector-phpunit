<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\AnnotationsToAttributes\Rector\ClassMethod\DependsAnnotationWithValueToAttributeRector;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->import(__DIR__ . '/../../../../../../config/config.php');

    $rectorConfig->rule(DependsAnnotationWithValueToAttributeRector::class);
};
