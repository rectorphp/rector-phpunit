<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\Rector\Class_\AddSeeTestAnnotationRector;
use Rector\PHPUnit\Rector\Class_\ConstructClassMethodToSetUpTestCaseRector;
use Rector\PHPUnit\Rector\Class_\PreferPHPUnitThisCallRector;
use Rector\PHPUnit\Rector\Class_\YieldDataProviderRector;
use Rector\PHPUnit\Rector\Foreach_\SimplifyForeachInstanceOfRector;
use Rector\PHPUnit\Rector\MethodCall\AssertCompareToSpecificMethodRector;
use Rector\PHPUnit\Rector\MethodCall\AssertComparisonToSpecificMethodRector;
use Rector\PHPUnit\Rector\MethodCall\AssertEqualsToSameRector;
use Rector\PHPUnit\Rector\MethodCall\AssertFalseStrposToContainsRector;
use Rector\PHPUnit\Rector\MethodCall\AssertInstanceOfComparisonRector;
use Rector\PHPUnit\Rector\MethodCall\AssertIssetToSpecificMethodRector;
use Rector\PHPUnit\Rector\MethodCall\AssertNotOperatorRector;
use Rector\PHPUnit\Rector\MethodCall\AssertPropertyExistsRector;
use Rector\PHPUnit\Rector\MethodCall\AssertRegExpRector;
use Rector\PHPUnit\Rector\MethodCall\AssertSameBoolNullToSpecificMethodRector;
use Rector\PHPUnit\Rector\MethodCall\AssertSameTrueFalseToAssertTrueFalseRector;
use Rector\PHPUnit\Rector\MethodCall\AssertTrueFalseInternalTypeToSpecificMethodRector;
use Rector\PHPUnit\Rector\MethodCall\AssertTrueFalseToSpecificMethodRector;
use Rector\PHPUnit\Rector\MethodCall\RemoveExpectAnyFromMockRector;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->rules([
        RemoveExpectAnyFromMockRector::class,
        AddSeeTestAnnotationRector::class,
        ConstructClassMethodToSetUpTestCaseRector::class,
        AssertSameTrueFalseToAssertTrueFalseRector::class,
        AssertEqualsToSameRector::class,
        PreferPHPUnitThisCallRector::class,
        YieldDataProviderRector::class,

        // sepcific asserts
        AssertCompareToSpecificMethodRector::class,
        AssertComparisonToSpecificMethodRector::class,
        AssertNotOperatorRector::class,
        AssertTrueFalseToSpecificMethodRector::class,
        AssertSameBoolNullToSpecificMethodRector::class,
        AssertFalseStrposToContainsRector::class,
        AssertTrueFalseInternalTypeToSpecificMethodRector::class,
        AssertIssetToSpecificMethodRector::class,
        AssertInstanceOfComparisonRector::class,
        AssertPropertyExistsRector::class,
        AssertRegExpRector::class,
        SimplifyForeachInstanceOfRector::class,
    ]);
};
