<?php

namespace Rector\PHPUnit\Tests\PHPUnit80\Rector\MethodCall\SpecificAssertInternalTypeRector\Fixture;

final class SomeTest extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $value = 'value';
        $this->assertInternalType('string', $value);
        $this->assertInternalType('array', $value);

        $this->assertNotInternalType('bool', $value, 'message');
        $this->assertNotInternalType('boolean', $value, 'message');
        $this->assertNotInternalType('callable', $value, 'message');
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit80\Rector\MethodCall\SpecificAssertInternalTypeRector\Fixture;

final class SomeTest extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $value = 'value';
        $this->assertIsString($value);
        $this->assertIsArray($value);

        $this->assertIsNotBool($value, 'message');
        $this->assertIsNotBool($value, 'message');
        $this->assertIsNotCallable($value, 'message');
    }
}

?>
