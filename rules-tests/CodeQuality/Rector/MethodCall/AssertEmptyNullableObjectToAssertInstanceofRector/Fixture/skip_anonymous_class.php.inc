<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertEmptyNullableObjectToAssertInstanceofRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipAnonymousClass extends TestCase
{
    public function test()
    {
        $someObject = mt_rand(0, 1) ? new class {
            public array $items = [];
        } : null;

        $this->assertNotNull($someObject);
    }
}
