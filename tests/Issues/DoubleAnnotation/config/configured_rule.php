<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\AnnotationsToAttributes\Rector\Class_\CoversAnnotationWithValueToAttributeRector;
use Rector\PHPUnit\AnnotationsToAttributes\Rector\ClassMethod\DataProviderAnnotationToAttributeRector;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->import(__DIR__ . '/../../../../config/config.php');

    $rectorConfig->rules([
        DataProviderAnnotationToAttributeRector::class,
        CoversAnnotationWithValueToAttributeRector::class,
    ]);
};
