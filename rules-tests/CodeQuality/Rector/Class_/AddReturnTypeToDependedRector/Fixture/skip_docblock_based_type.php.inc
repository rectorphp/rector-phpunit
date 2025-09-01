<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\AddReturnTypeToDependedRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipDocblockBasedType extends TestCase
{
    /**
     * @param int $someValue
     */
    public function test($someValue)
    {
        return $someValue;
    }
}
