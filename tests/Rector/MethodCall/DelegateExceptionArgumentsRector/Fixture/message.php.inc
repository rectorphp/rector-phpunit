<?php

namespace Rector\PHPUnit\Tests\Rector\MethodCall\DelegateExceptionArgumentsRector\Fixture;

final class MyMessageTest extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $this->setExpectedException('FirstException');
        // with message
        $this->setExpectedException('SecondException', $message);
        // with code
        self::setExpectedException('ThirdException', $message, 101);
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
        $this->expectException('FirstException');
        $this->expectExceptionMessage($message);
        self::expectExceptionMessage($message);
        self::expectExceptionCode(101);
        self::expectException('ThirdException');
        // with code
        self::expectException('ThirdException');
    }
}

?>
