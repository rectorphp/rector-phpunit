<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\CodeQuality\Rector\Class_\AddCoversClassAttributeRector;
use Rector\PHPUnit\ValueObject\TestClassSuffixesConfig;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->ruleWithConfiguration(AddCoversClassAttributeRector::class, [
        new TestClassSuffixesConfig(['Test', 'TestCase', 'FunctionalTest', 'IntegrationTest']),
    ]);
};
