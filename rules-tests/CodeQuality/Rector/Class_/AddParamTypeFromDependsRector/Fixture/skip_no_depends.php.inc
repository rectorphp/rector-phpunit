<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\AddParamTypeFromDependsRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipNoDepends extends TestCase
{
    public function test(): \stdClass
    {
        return new \stdClass();
    }

    public function testNoDepends($value)
    {
    }
}
