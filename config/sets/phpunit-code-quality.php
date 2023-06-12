<?php

declare(strict_types=1);

use Rector\CodingStyle\Rector\ClassMethod\ReturnArrayClassMethodToYieldRector;
use Rector\CodingStyle\ValueObject\ReturnArrayClassMethodToYield;
use Rector\Config\RectorConfig;
use Rector\PHPUnit\Rector\Class_\AddSeeTestAnnotationRector;
use Rector\PHPUnit\Rector\Class_\ConstructClassMethodToSetUpTestCaseRector;
use Rector\PHPUnit\Rector\Class_\PreferPHPUnitThisCallRector;
use Rector\PHPUnit\Rector\MethodCall\AssertCompareToSpecificMethodRector;
use Rector\PHPUnit\Rector\MethodCall\AssertComparisonToSpecificMethodRector;
use Rector\PHPUnit\Rector\MethodCall\AssertEqualsToSameRector;
use Rector\PHPUnit\Rector\MethodCall\AssertSameTrueFalseToAssertTrueFalseRector;
use Rector\PHPUnit\Rector\MethodCall\RemoveExpectAnyFromMockRector;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->rules([
        RemoveExpectAnyFromMockRector::class,
        AddSeeTestAnnotationRector::class,
        ConstructClassMethodToSetUpTestCaseRector::class,
        AssertSameTrueFalseToAssertTrueFalseRector::class,
        AssertEqualsToSameRector::class,
        AssertCompareToSpecificMethodRector::class,
        AssertComparisonToSpecificMethodRector::class,
        PreferPHPUnitThisCallRector::class,
    ]);

    $rectorConfig->ruleWithConfiguration(ReturnArrayClassMethodToYieldRector::class, [
        new ReturnArrayClassMethodToYield('PHPUnit\Framework\TestCase', 'provide*'),
        new ReturnArrayClassMethodToYield('PHPUnit\Framework\TestCase', 'dataProvider*'),
    ]);
};
