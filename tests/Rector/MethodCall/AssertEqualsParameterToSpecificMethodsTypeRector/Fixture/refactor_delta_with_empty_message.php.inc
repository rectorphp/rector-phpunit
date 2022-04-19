<?php

namespace Rector\PHPUnit\Tests\Rector\MethodCall\AssertEqualsParameterToSpecificMethodsTypeRector\Fixture;

use PHPUnit\Framework\TestCase;

final class RefactorDeltaWithEmptyMessage extends TestCase
{
    public function test()
    {
        $value = 'value';
        $this->assertEquals('string', $value, '', 5.0);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\Rector\MethodCall\AssertEqualsParameterToSpecificMethodsTypeRector\Fixture;

use PHPUnit\Framework\TestCase;

final class RefactorDeltaWithEmptyMessage extends TestCase
{
    public function test()
    {
        $value = 'value';
        $this->assertEqualsWithDelta('string', $value, 5.0);
    }
}

?>
