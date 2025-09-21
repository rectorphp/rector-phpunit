<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\ScalarArgumentToExpectedParamTypeRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\ScalarArgumentToExpectedParamTypeRector\Source\ValueObjectWithoutConstructor;

final class SkipWithoutConstruct extends TestCase
{
    public function test()
    {
        $valueObject = new ValueObjectWithoutConstructor(123.456, '123');
    }
}

?>