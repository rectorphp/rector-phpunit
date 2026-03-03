<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\CallLike\CreateStubOverCreateMockArgRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\PHPUnit120\Rector\CallLike\CreateStubOverCreateMockArgRector\Source\AnyClass;

class SkipFirstClassCallable extends TestCase
{
    public function testThat()
    {
        AnyClass::staticRun(...);
    }
}
