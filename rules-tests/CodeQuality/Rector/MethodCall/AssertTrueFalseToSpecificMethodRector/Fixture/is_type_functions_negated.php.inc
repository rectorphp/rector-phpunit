<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertTrueFalseToSpecificMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class IsTypeFunctionsNegated extends TestCase
{
    public function test()
    {
        $this->assertFalse(is_callable($value));
        $this->assertNotTrue(is_array($value));
        $this->assertNotFalse(is_string($value));
        self::assertFalse(is_object($value), 'the value must not be an object');
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertTrueFalseToSpecificMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class IsTypeFunctionsNegated extends TestCase
{
    public function test()
    {
        $this->assertIsNotCallable($value);
        $this->assertIsNotArray($value);
        $this->assertIsString($value);
        self::assertIsNotObject($value, 'the value must not be an object');
    }
}

?>
