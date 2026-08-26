<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertTrueFalseToSpecificMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class IsTypeFunctions extends TestCase
{
    public function test()
    {
        $this->assertTrue(is_array($value));
        $this->assertTrue(is_bool($value));
        $this->assertTrue(is_callable($value));
        $this->assertTrue(is_float($value));
        $this->assertTrue(is_int($value));
        $this->assertTrue(is_iterable($value));
        $this->assertTrue(is_numeric($value));
        $this->assertTrue(is_object($value));
        $this->assertTrue(is_scalar($value));
        $this->assertTrue(is_string($value), 'the value must be a string');
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertTrueFalseToSpecificMethodRector\Fixture;

use PHPUnit\Framework\TestCase;

final class IsTypeFunctions extends TestCase
{
    public function test()
    {
        $this->assertIsArray($value);
        $this->assertIsBool($value);
        $this->assertIsCallable($value);
        $this->assertIsFloat($value);
        $this->assertIsInt($value);
        $this->assertIsIterable($value);
        $this->assertIsNumeric($value);
        $this->assertIsObject($value);
        $this->assertIsScalar($value);
        $this->assertIsString($value, 'the value must be a string');
    }
}

?>
