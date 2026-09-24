<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\FlipAssertRector\Fixture;

final class ArrayLiteralWithVariable extends \PHPUnit\Framework\TestCase
{
    public function test($result, $model, $response, $transformations)
    {
        $this->assertEquals($model->value, ['transformations' => $transformations]);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\FlipAssertRector\Fixture;

final class ArrayLiteralWithVariable extends \PHPUnit\Framework\TestCase
{
    public function test($result, $model, $response, $transformations)
    {
        $this->assertEquals(['transformations' => $transformations], $model->value);
    }
}

?>
