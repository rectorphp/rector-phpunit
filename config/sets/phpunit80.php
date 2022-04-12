<?php

declare(strict_types=1);

use PHPStan\Type\MixedType;
use PHPStan\Type\VoidType;
use Rector\Config\RectorConfig;
use Rector\Core\ValueObject\MethodName;
use Rector\PHPUnit\Rector\MethodCall\AssertEqualsParameterToSpecificMethodsTypeRector;
use Rector\PHPUnit\Rector\MethodCall\SpecificAssertContainsRector;
use Rector\PHPUnit\Rector\MethodCall\SpecificAssertInternalTypeRector;
use Rector\Renaming\Rector\Name\RenameClassRector;
use Rector\TypeDeclaration\Rector\ClassMethod\AddParamTypeDeclarationRector;
use Rector\TypeDeclaration\Rector\ClassMethod\AddReturnTypeDeclarationRector;
use Rector\TypeDeclaration\ValueObject\AddParamTypeDeclaration;
use Rector\TypeDeclaration\ValueObject\AddReturnTypeDeclaration;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->import(__DIR__ . '/phpunit-exception.php');

    $services = $rectorConfig->services();

    $services->set(AddParamTypeDeclarationRector::class)
        ->configure([
            // https://github.com/rectorphp/rector/issues/1024 - no type, $dataName
            new AddParamTypeDeclaration('PHPUnit\Framework\TestCase', MethodName::CONSTRUCT, 2, new MixedType()),
        ]);

    $services->set(SpecificAssertContainsRector::class);

    $services->set(SpecificAssertInternalTypeRector::class);

    $services->set(RenameClassRector::class)
        ->configure([
            # https://github.com/sebastianbergmann/phpunit/issues/3123
            'PHPUnit_Framework_MockObject_MockObject' => 'PHPUnit\Framework\MockObject\MockObject',
        ]);

    $services->set(AssertEqualsParameterToSpecificMethodsTypeRector::class);

    $services->set(AddReturnTypeDeclarationRector::class)
        ->configure([
            new AddReturnTypeDeclaration('PHPUnit\Framework\TestCase', 'setUpBeforeClass', new VoidType()),
            new AddReturnTypeDeclaration('PHPUnit\Framework\TestCase', 'setUp', new VoidType()),
            new AddReturnTypeDeclaration('PHPUnit\Framework\TestCase', 'assertPreConditions', new VoidType()),
            new AddReturnTypeDeclaration('PHPUnit\Framework\TestCase', 'assertPostConditions', new VoidType()),
            new AddReturnTypeDeclaration('PHPUnit\Framework\TestCase', 'tearDown', new VoidType()),
            new AddReturnTypeDeclaration('PHPUnit\Framework\TestCase', 'tearDownAfterClass', new VoidType()),
            new AddReturnTypeDeclaration('PHPUnit\Framework\TestCase', 'onNotSuccessfulTest', new VoidType()),
        ]);
};
