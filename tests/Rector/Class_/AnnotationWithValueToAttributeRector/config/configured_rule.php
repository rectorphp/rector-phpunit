<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\Rector\Class_\AnnotationWithValueToAttributeRector;
use Rector\PHPUnit\ValueObject\AnnotationWithValueToAttribute;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->import(__DIR__ . '/../../../../../config/config.php');

    $rectorConfig->ruleWithConfiguration(AnnotationWithValueToAttributeRector::class, [
        new AnnotationWithValueToAttribute(
            'backupGlobals',
            'PHPUnit\Framework\Attributes\BackupGlobals',
            [
                'enabled' => true,
                'disabled' => false,
            ]
        ),
    ]);
};
