<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\CodingStyle\Rector\ClassMethod\ReturnArrayClassMethodToYieldRector;
use Rector\CodingStyle\ValueObject\ReturnArrayClassMethodToYield;
use Rector\PHPUnit\Rector\Class_\AddSeeTestAnnotationRector;
use Rector\PHPUnit\Rector\Class_\ConstructClassMethodToSetUpTestCaseRector;
use Rector\PHPUnit\Rector\MethodCall\AssertCompareToSpecificMethodRector;
use Rector\PHPUnit\Rector\MethodCall\AssertComparisonToSpecificMethodRector;
use Rector\PHPUnit\Rector\MethodCall\AssertEqualsToSameRector;
use Rector\PHPUnit\Rector\MethodCall\AssertSameTrueFalseToAssertTrueFalseRector;
use Rector\PHPUnit\Rector\MethodCall\RemoveExpectAnyFromMockRector;

return static function (RectorConfig $containerConfigurator): void {
    $services = $containerConfigurator->services();
    $services->set(RemoveExpectAnyFromMockRector::class);
    $services->set(AddSeeTestAnnotationRector::class);

    $services->set(ReturnArrayClassMethodToYieldRector::class)
        ->configure([
            new ReturnArrayClassMethodToYield('PHPUnit\Framework\TestCase', 'provide*'),
            new ReturnArrayClassMethodToYield('PHPUnit\Framework\TestCase', 'dataProvider*'),
        ]);

    $services->set(ConstructClassMethodToSetUpTestCaseRector::class);
    $services->set(AssertSameTrueFalseToAssertTrueFalseRector::class);
    $services->set(AssertEqualsToSameRector::class);
    $services->set(AssertCompareToSpecificMethodRector::class);
    $services->set(AssertComparisonToSpecificMethodRector::class);
};
