<?php

// skip: non-string argument (enum case) should not crash

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\Class_\AssertIsTypeMethodCallRector\Fixture;

use PHPUnit\Framework\TestCase;

enum SkipNonStringArgEnum
{
    case ONE;
}

final class SkipNonStringArg extends TestCase
{
    public function testMethod(): void
    {
        $this->assertThat([], $this->isType(SkipNonStringArgEnum::ONE));
    }
}
