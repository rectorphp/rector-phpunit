<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\ScalarArgumentToExpectedParamTypeRector\Source;

final class SomeClassWithSetter
{
    public function setPhoneNumber(string $phoneNumber)
    {
    }

    /**
     * @param string $passportId
     */
    public function setMagicType($passportId)
    {

    }

    public function setUnionType(int|string $unionValue)
    {

    }
}
