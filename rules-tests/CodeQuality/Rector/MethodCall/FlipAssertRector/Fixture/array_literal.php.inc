<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\FlipAssertRector\Fixture;

final class ArrayLiteral extends \PHPUnit\Framework\TestCase
{
    public function test($result, $model, $response, $transformations)
    {
        $this->assertSame($response->json(), ['id' => 1, 'status' => SomeEnum::Active]);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\FlipAssertRector\Fixture;

final class ArrayLiteral extends \PHPUnit\Framework\TestCase
{
    public function test($result, $model, $response, $transformations)
    {
        $this->assertSame(['id' => 1, 'status' => SomeEnum::Active], $response->json());
    }
}

?>
