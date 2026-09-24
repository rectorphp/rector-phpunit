<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\FlipAssertRector\Fixture;

final class SkipActualArrayLiteral extends \PHPUnit\Framework\TestCase
{
    public function test($result, $model, $response, $transformations)
    {
        $this->assertSame($result, [$model->x, $model->y]);
        $this->assertSame($result, [$model->getX()]);
    }
}

?>
