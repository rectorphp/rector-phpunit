<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\MethodCall\DelegateExceptionArgumentsRector\Fixture;

final class BeforeTestStmt extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $this->setExpectedException('SecondException', $message);
        $this->execute();
    }

    private function execute()
    {}
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\MethodCall\DelegateExceptionArgumentsRector\Fixture;

final class BeforeTestStmt extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $this->expectException('SecondException');
        $this->expectExceptionMessage($message);
        $this->execute();
    }

    private function execute()
    {}
}

?>
