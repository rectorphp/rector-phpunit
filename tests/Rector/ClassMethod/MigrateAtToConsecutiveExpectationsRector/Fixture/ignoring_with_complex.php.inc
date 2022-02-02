<?php

namespace Rector\PHPUnit\Tests\Rector\ClassMethod\MigrateAtToConsecutiveExpectationsRector\Fixture;

use PHPUnit\Framework\TestCase;

final class IgnoringWithComplex extends TestCase
{
    public function barTest()
    {
        $mocks[MyClass::class]->expects($this->at(0))->method('convert')->with(
            Money::EUR(100),
            new Currency('USD')
        )->willReturn(Money::USD(120));
    }
}
