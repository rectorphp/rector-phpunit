<?php

namespace Rector\PHPUnit\Tests\Rector\MethodCall\DelegateExceptionArgumentsRector\Fixture;

final class MyMessageTest extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $this->setExpectedException('SomeException');
        // with message
        $this->setExpectedException('SomeException', $message);
        // with code
        self::setExpectedException('SomeException', $message, 101);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\Rector\MethodCall\DelegateExceptionArgumentsRector\Fixture;

final class MyMessageTest extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $this->expectException('SomeException');
        $this->expectExceptionMessage($message);
        self::expectExceptionMessage($message);
        self::expectExceptionCode(101);
        self::expectException('SomeException');
        // with code
        self::expectException('SomeException');
    }
}

?>
