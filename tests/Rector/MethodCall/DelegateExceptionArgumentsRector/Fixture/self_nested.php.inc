<?php

use PHPUnit\Framework\TestCase;

class ArrayInputTest extends TestCase
{
    public function testParseInvalidInput($expectedExceptionMessage)
    {
        if (method_exists($this, 'expectException')) {
            $this->setExpectedException('SomeException', $message);
        } else {
            $this->setExpectedException('InvalidArgumentException', $expectedExceptionMessage);
        }
    }
}

?>
-----
<?php

use PHPUnit\Framework\TestCase;

class ArrayInputTest extends TestCase
{
    public function testParseInvalidInput($expectedExceptionMessage)
    {
        if (method_exists($this, 'expectException')) {
            $this->expectExceptionMessage($message);
            $this->expectException('SomeException');
        } else {
            $this->expectExceptionMessage($expectedExceptionMessage);
            $this->expectException('InvalidArgumentException');
        }
    }
}

?>
