<?php

namespace Rector\PHPUnit\Tests\Rector\MethodCall\DelegateExceptionArgumentsRector\Fixture;

final class BareMethodRenameTest extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $this->setExpectedException('FirstException');
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\Rector\MethodCall\DelegateExceptionArgumentsRector\Fixture;

final class BareMethodRenameTest extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $this->expectException('FirstException');
    }
}

?>
