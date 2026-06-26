<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\Class_\PreferTestsWithCamelCaseRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SkipExistingNameTest extends TestCase
{
    public function test_me()
    {
    }

    public function testMe()
    {
    }
}
