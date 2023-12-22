<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\MethodCall\DelegateExceptionArgumentsRector\Fixture;

final class BeforeTestStmtWithCode extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $this->setExpectedException('SecondException', $message, 101);
        $this->execute();
    }

    private function execute()
    {}
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\MethodCall\DelegateExceptionArgumentsRector\Fixture;

final class BeforeTestStmtWithCode extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $this->expectException('SecondException');
        $this->expectExceptionMessage($message);
        $this->expectExceptionCode(101);
        $this->execute();
    }

    private function execute()
    {}
}

?>
