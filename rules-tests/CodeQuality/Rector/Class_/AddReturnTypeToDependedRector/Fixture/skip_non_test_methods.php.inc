<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\AddReturnTypeToDependedRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipNonTestMethods extends TestCase
{
    public function nonTestMethod()
    {
        return new \stdClass();
    }

    private function testNotMethod()
    {
        return new \stdClass();
    }
}
