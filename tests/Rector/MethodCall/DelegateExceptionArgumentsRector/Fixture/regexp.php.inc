<?php

final class MyRegexpTest extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        self::setExpectedExceptionRegExp('SomeException', 'SomREGEPX');
    }
}

?>
-----
<?php

final class MyRegexpTest extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        self::expectExceptionMessageRegExp('SomREGEPX');
        self::expectException('SomeException');
    }
}

?>
