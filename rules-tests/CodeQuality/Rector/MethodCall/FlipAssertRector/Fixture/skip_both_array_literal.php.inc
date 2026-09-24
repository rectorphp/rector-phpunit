<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\FlipAssertRector\Fixture;

final class SkipBothArrayLiteral extends \PHPUnit\Framework\TestCase
{
    public function test($result, $model, $response, $transformations)
    {
        $this->assertSame(['id' => 1], [1, 2]);
    }
}

?>
