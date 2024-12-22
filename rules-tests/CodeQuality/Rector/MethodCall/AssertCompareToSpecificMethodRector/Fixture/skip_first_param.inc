<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertCompareToSpecificMethodRector\Fixture;

final class SkipFirstParam extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $this->assertSame(count($something), 5);
        $this->assertSame(get_class($something), 'stdClass');
    }
}

?>
    -----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertCompareToSpecificMethodRector\Fixture;

final class SkipFirstParam extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $this->assertSame(count($something), 5);
        $this->assertSame(get_class($something), 'stdClass');
    }
}

?>
