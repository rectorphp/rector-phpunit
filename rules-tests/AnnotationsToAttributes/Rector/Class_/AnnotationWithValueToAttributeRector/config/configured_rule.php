<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\AnnotationsToAttributes\Rector\Class_\AnnotationWithValueToAttributeRector;
use Rector\PHPUnit\ValueObject\AnnotationWithValueToAttribute;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->ruleWithConfiguration(AnnotationWithValueToAttributeRector::class, [
        new AnnotationWithValueToAttribute('backupGlobals', 'PHPUnit\Framework\Attributes\BackupGlobals', [
            'enabled' => true,
            'disabled' => false,
        ]),
        new AnnotationWithValueToAttribute('dataProvider', 'PHPUnit\Framework\Attributes\DataProvider'),
        new AnnotationWithValueToAttribute('uses', 'PHPUnit\Framework\Attributes\UsesClass'),
    ]);
};
