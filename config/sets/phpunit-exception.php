<?php

declare(strict_types=1);

use Rector\PHPUnit\Rector\ClassMethod\ExceptionAnnotationRector;
use Rector\PHPUnit\Rector\MethodCall\DelegateExceptionArgumentsRector;
use Rector\Renaming\Rector\MethodCall\RenameMethodRector;
use Rector\Renaming\ValueObject\MethodCallRename;
use Symfony\Component\DependencyInjection\Loader\Configurator\ContainerConfigurator;

return static function (\Rector\Config\RectorConfig $containerConfigurator): void {
    $services = $containerConfigurator->services();

    # handles 2nd and 3rd argument of setExpectedException
    $services->set(DelegateExceptionArgumentsRector::class);

    $services->set(ExceptionAnnotationRector::class);

    $services->set(RenameMethodRector::class)
        ->configure([
            new MethodCallRename('PHPUnit\Framework\TestClass', 'setExpectedException', 'expectedException'),
            new MethodCallRename('PHPUnit\Framework\TestClass', 'setExpectedExceptionRegExp', 'expectedException'),
        ]);
};
