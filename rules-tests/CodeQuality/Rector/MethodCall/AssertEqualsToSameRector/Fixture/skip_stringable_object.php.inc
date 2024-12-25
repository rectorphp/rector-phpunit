<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertEqualsToSameRector\Fixture;

use PHPUnit\Framework\TestCase;
use Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertEqualsToSameRector\Source\SimpleStringable;

final class SkipStringableObject extends TestCase
{
    public function test()
    {
        $this->assertEquals('value', new SimpleStringable());
    }
}
