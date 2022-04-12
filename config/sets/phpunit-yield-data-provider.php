<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\CodingStyle\Rector\ClassMethod\ReturnArrayClassMethodToYieldRector;
use Rector\CodingStyle\ValueObject\ReturnArrayClassMethodToYield;

return static function (RectorConfig $containerConfigurator): void {
    $services = $containerConfigurator->services();

    $services->set(ReturnArrayClassMethodToYieldRector::class)
        ->configure([
            new ReturnArrayClassMethodToYield('PHPUnit\Framework\TestCase', 'provide*'),
            new ReturnArrayClassMethodToYield('PHPUnit\Framework\TestCase', 'dataProvider*'),
        ]);
};
