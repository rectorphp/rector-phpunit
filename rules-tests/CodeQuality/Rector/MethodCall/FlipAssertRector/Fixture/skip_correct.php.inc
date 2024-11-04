<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\FlipAssertRector\Fixture;

final class SkipCorrect extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $result = '...';
        $this->assertSame('expected', $result);
    }
}
