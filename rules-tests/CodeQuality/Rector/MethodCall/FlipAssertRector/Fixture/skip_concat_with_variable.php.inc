<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\FlipAssertRector\Fixture;

final class SkipConcatWithVariable extends \PHPUnit\Framework\TestCase
{
    public function test($result, $id)
    {
        $this->assertSame($result->getId(), 'id-' . $id);
    }
}

?>
