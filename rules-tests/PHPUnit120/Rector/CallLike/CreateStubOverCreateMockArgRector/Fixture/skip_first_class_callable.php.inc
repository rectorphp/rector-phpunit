<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\CallLike\CreateStubOverCreateMockArgRector\Fixture;

use PHPUnit\Framework\TestCase;
use Utils\PHPStan\Tests\Rule\PHPUnit\StubOverMockArgRule\Source\AnyClass;

class SkipFirstClassCallable extends TestCase
{
    public function testThat()
    {
        AnyClass::staticRun(...);
    }
}
