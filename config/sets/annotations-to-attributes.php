<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\Php80\Rector\Class_\AnnotationToAttributeRector;
use Rector\Php80\ValueObject\AnnotationToAttribute;
use Rector\PHPUnit\Rector\Class_\AnnotationWithValueToAttributeRector;
use Rector\PHPUnit\ValueObject\AnnotationWithValueToAttribute;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->ruleWithConfiguration(AnnotationWithValueToAttributeRector::class, [
        new AnnotationWithValueToAttribute('backupGlobals', 'PHPUnit\Framework\Attributes\BackupGlobals', [
            'enabled' => true,
            'disabled' => false,
        ]),
        new AnnotationWithValueToAttribute('backupStaticAttributes', 'PHPUnit\Framework\Attributes\BackupStaticProperties', [
            'enabled' => true,
            'disabled' => false,
        ]),
        new AnnotationWithValueToAttribute('preserveGlobalState', 'PHPUnit\Framework\Attributes\PreserveGlobalState', [
            'enabled' => true,
            'disabled' => false,
        ]),

        // new AnnotationToAttribute('covers', 'PHPUnit\Framework\Attributes\CoversClass'),
        // new AnnotationToAttribute('covers', 'PHPUnit\Framework\Attributes\CoversFunction'),
        // new AnnotationToAttribute('dataProvider', 'PHPUnit\Framework\Attributes\DataProvider'),
        // new AnnotationToAttribute('dataProvider', 'PHPUnit\Framework\Attributes\DataProviderExternal'),
        // new AnnotationToAttribute('depends', 'PHPUnit\Framework\Attributes\Depends'),
        // new AnnotationToAttribute('depends', 'PHPUnit\Framework\Attributes\DependsExternal'),
        // new AnnotationToAttribute('PHPUnit\Framework\Attributes\DependsExternalUsingDeepClone'),
        // new AnnotationToAttribute('PHPUnit\Framework\Attributes\DependsExternalUsingShallowClone'),
        // new AnnotationToAttribute('PHPUnit\Framework\Attributes\DependsOnClass'),
        // new AnnotationToAttribute('PHPUnit\Framework\Attributes\DependsOnClassUsingDeepClone'),
        // new AnnotationToAttribute('PHPUnit\Framework\Attributes\DependsOnClassUsingShallowClone'),
        // new AnnotationToAttribute('PHPUnit\Framework\Attributes\DependsUsingDeepClone'),
        // new AnnotationToAttribute('PHPUnit\Framework\Attributes\DependsUsingShallowClone'),
        // new AnnotationToAttribute('PHPUnit\Framework\Attributes\ExcludeGlobalVariableFromBackup'),
        // new AnnotationToAttribute('PHPUnit\Framework\Attributes\ExcludeStaticPropertyFromBackup'),
        // new AnnotationToAttribute('group', 'PHPUnit\Framework\Attributes\Group'),

        // new AnnotationToAttribute('PHPUnit\Framework\Attributes\RequiresFunction'),
        // new AnnotationToAttribute('PHPUnit\Framework\Attributes\RequiresMethod'),
        // new AnnotationToAttribute('PHPUnit\Framework\Attributes\RequiresOperatingSystem'),
        // new AnnotationToAttribute('PHPUnit\Framework\Attributes\RequiresOperatingSystemFamily'),
        // new AnnotationToAttribute('PHPUnit\Framework\Attributes\RequiresPhp'),
        // new AnnotationToAttribute('PHPUnit\Framework\Attributes\RequiresPhpExtension'),
        // new AnnotationToAttribute('PHPUnit\Framework\Attributes\RequiresPhpunit'),
        // new AnnotationToAttribute('PHPUnit\Framework\Attributes\RequiresSetting'),
        // new AnnotationToAttribute('PHPUnit\Framework\Attributes\RunClassInSeparateProcess'),
        // new AnnotationToAttribute('PHPUnit\Framework\Attributes\TestDox'),
        // new AnnotationToAttribute('PHPUnit\Framework\Attributes\TestWith'),
        // new AnnotationToAttribute('PHPUnit\Framework\Attributes\TestWithJson'),
        // new AnnotationToAttribute('ticket', 'PHPUnit\Framework\Attributes\Ticket'),
        // new AnnotationToAttribute('PHPUnit\Framework\Attributes\UsesClass'),
        // new AnnotationToAttribute('PHPUnit\Framework\Attributes\UsesFunction'),
    ]);

    $rectorConfig->ruleWithConfiguration(AnnotationToAttributeRector::class, [
        // @see https://github.com/sebastianbergmann/phpunit/issues/4502
        new AnnotationToAttribute('after', 'PHPUnit\Framework\Attributes\After'),
        new AnnotationToAttribute('afterClass', 'PHPUnit\Framework\Attributes\AfterClass'),
        new AnnotationToAttribute('before', 'PHPUnit\Framework\Attributes\Before'),
        new AnnotationToAttribute('beforeClass', 'PHPUnit\Framework\Attributes\BeforeClass'),
        new AnnotationToAttribute('codeCoverageIgnore', 'PHPUnit\Framework\Attributes\CodeCoverageIgnore'),
        new AnnotationToAttribute('coversNothing', 'PHPUnit\Framework\Attributes\CoversNothing'),
        new AnnotationToAttribute('doesNotPerformAssertions', 'PHPUnit\Framework\Attributes\DoesNotPerformAssertions'),
        new AnnotationToAttribute('large', 'PHPUnit\Framework\Attributes\Large'),
        new AnnotationToAttribute('medium', 'PHPUnit\Framework\Attributes\Medium'),
        new AnnotationToAttribute('preCondition', 'PHPUnit\Framework\Attributes\PostCondition'),
        new AnnotationToAttribute('postCondition', 'PHPUnit\Framework\Attributes\PreCondition'),
        new AnnotationToAttribute('runInSeparateProcess', 'PHPUnit\Framework\Attributes\RunInSeparateProcess'),
        new AnnotationToAttribute(
            'runTestsInSeparateProcesses',
            'PHPUnit\Framework\Attributes\RunTestsInSeparateProcesses'
        ),
        new AnnotationToAttribute('small', 'PHPUnit\Framework\Attributes\Small'),
        new AnnotationToAttribute('test', 'PHPUnit\Framework\Attributes\Test'),
    ]);
};
