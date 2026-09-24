<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\FlipAssertRector\Fixture;

final class SkipCorrectCanonicalizing extends \PHPUnit\Framework\TestCase
{
    public function test($result, $model, $response, $transformations)
    {
        $this->assertEqualsCanonicalizing([1, 2], $result);
        $this->assertEqualsWithDelta(1.5, $result, 0.01);
    }
}

?>
