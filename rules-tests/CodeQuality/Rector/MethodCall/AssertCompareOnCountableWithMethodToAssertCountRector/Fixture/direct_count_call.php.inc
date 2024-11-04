<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertCompareOnCountableWithMethodToAssertCountRector\Fixture;

final class DirectCountCall extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $items = [1, 2, 3];
        $this->assertSame(3, count($items));
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertCompareOnCountableWithMethodToAssertCountRector\Fixture;

final class DirectCountCall extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $items = [1, 2, 3];
        $this->assertCount(3, $items);
    }
}

?>
