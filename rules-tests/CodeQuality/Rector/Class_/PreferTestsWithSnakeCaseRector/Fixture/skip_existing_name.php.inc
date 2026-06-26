<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\PreferTestsWithSnakeCaseRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipExistingNameTest extends TestCase
{
    public function testMe()
    {
    }

    public function test_me()
    {
    }
}
