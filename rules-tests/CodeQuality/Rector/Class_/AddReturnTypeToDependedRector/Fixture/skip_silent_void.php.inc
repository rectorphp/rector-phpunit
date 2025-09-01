<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\AddReturnTypeToDependedRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipSilentVoid extends TestCase
{
    public function test()
    {
        if (rand(0, 1)) {
            return;
        }

        return new \stdClass();
    }
}
