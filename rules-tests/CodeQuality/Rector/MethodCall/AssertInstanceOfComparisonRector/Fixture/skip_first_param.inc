<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertInstanceOfComparisonRector\Fixture;

final class SkipFirstParam extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $this->assertSame(get_class($something), 'stdClass');
    }
}

?>
    -----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertInstanceOfComparisonRector\Fixture;

final class SkipFirstParam extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $this->assertSame(get_class($something), 'stdClass');
    }
}

?>
