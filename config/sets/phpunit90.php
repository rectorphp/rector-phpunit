<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\PHPUnit\Rector\Class_\TestListenerToHooksRector;
use Rector\PHPUnit\Rector\MethodCall\ExplicitPhpErrorApiRector;
use Rector\PHPUnit\Rector\MethodCall\SpecificAssertContainsWithoutIdentityRector;
use Rector\Renaming\Rector\MethodCall\RenameMethodRector;
use Rector\Renaming\ValueObject\MethodCallRename;

return static function (RectorConfig $rectorConfig): void {
    $services = $rectorConfig->services();

    $services->set(TestListenerToHooksRector::class);

    $services->set(ExplicitPhpErrorApiRector::class);

    $services->set(SpecificAssertContainsWithoutIdentityRector::class);

    $services->set(RenameMethodRector::class)
        ->configure([
            // see https://github.com/sebastianbergmann/phpunit/issues/3957
            new MethodCallRename(
                'PHPUnit\Framework\TestCase',
                'expectExceptionMessageRegExp',
                'expectExceptionMessageMatches'
            ),
        ]);
};
