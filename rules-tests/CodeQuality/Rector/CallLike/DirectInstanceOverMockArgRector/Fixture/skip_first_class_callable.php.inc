<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\CallLike\DirectInstanceOverMockArgRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipFirstClassCallable extends TestCase
{
    public function testThat()
    {
        AnyClass::staticRun(...);
    }
}
