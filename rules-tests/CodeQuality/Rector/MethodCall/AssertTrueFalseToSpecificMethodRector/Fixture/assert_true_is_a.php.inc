<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertTrueFalseToSpecificMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AssertTrueIsA extends TestCase
{
    public function test()
    {
        $value = new \stdClass();

        $this->assertTrue(
            is_a($value, 'SomeClass')
        );

        $this->assertFalse(
            is_a($value, 'SomeClass')
        );
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertTrueFalseToSpecificMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class AssertTrueIsA extends TestCase
{
    public function test()
    {
        $value = new \stdClass();

        $this->assertInstanceOf('SomeClass', $value);

        $this->assertNotInstanceOf('SomeClass', $value);
    }
}

?>
