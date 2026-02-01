<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertThatToDirectAssertRector\Fixture;

final class SimpleAssertThat extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $this->assertThat('value', $this->equalTo('expectedValue'));
    }
}

?>
-----
<?php

declare(strict_types=1);

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertThatToDirectAssertRector\Fixture;

final class SimpleAssertThat extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $this->assertEquals('expectedValue', 'value');
    }
}

?>
