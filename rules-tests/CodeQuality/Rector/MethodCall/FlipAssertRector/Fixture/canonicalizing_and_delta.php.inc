<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\FlipAssertRector\Fixture;

final class CanonicalizingAndDelta extends \PHPUnit\Framework\TestCase
{
    public function test($result, $model, $response, $transformations)
    {
        $this->assertEqualsCanonicalizing($result, [1, 2]);
        $this->assertNotEqualsCanonicalizing($result, [3, 4]);
        $this->assertEqualsIgnoringCase($result, 'expected');
        $this->assertNotEqualsIgnoringCase($result, 'other');
        $this->assertEqualsWithDelta($result, 1.5, 0.01);
        $this->assertNotEqualsWithDelta($result, 2.5, 0.01);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\FlipAssertRector\Fixture;

final class CanonicalizingAndDelta extends \PHPUnit\Framework\TestCase
{
    public function test($result, $model, $response, $transformations)
    {
        $this->assertEqualsCanonicalizing([1, 2], $result);
        $this->assertNotEqualsCanonicalizing([3, 4], $result);
        $this->assertEqualsIgnoringCase('expected', $result);
        $this->assertNotEqualsIgnoringCase('other', $result);
        $this->assertEqualsWithDelta(1.5, $result, 0.01);
        $this->assertNotEqualsWithDelta(2.5, $result, 0.01);
    }
}

?>
