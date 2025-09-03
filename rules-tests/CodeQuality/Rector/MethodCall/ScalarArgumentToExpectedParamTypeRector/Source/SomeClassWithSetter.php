<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\ScalarArgumentToExpectedParamTypeRector\Source;

final class SomeClassWithSetter
{
    public function setPhoneNumber(string $phoneNumber)
    {
    }
}
