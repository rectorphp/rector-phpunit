<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertEqualsOrAssertSameFloatParameterToSpecificMethodsTypeRector\Fixture;

use PHPUnit\Framework\TestCase;

final class KeepDeltaMessage extends TestCase
{
    public function test()
    {
        $value = 10.20001;
        $this->assertSame(10.20, $value, 'Some message');
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertEqualsOrAssertSameFloatParameterToSpecificMethodsTypeRector\Fixture;

use PHPUnit\Framework\TestCase;

final class KeepDeltaMessage extends TestCase
{
    public function test()
    {
        $value = 10.20001;
        $this->assertEqualsWithDelta(10.20, $value, PHP_FLOAT_EPSILON, 'Some message');
    }
}

?>
