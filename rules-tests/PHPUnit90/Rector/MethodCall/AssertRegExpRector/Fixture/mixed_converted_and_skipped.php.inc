<?php

namespace Rector\PHPUnit\Tests\PHPUnit90\Rector\MethodCall\AssertRegExpRector\Fixture;

final class MixedConvertedAndSkipped extends \PHPUnit\Framework\TestCase
{
    public function testFoo(bool $expectMatch): void
    {
        $string = 'keys=1000';

        $this->assertSame(1, preg_match('/^keys=\d+/', $string));
        $this->assertSame($expectMatch ? 1 : 0, preg_match('/^keys=\d+/', $string));
        $this->assertEquals(0, preg_match('/^values=\d+/', $string));
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit90\Rector\MethodCall\AssertRegExpRector\Fixture;

final class MixedConvertedAndSkipped extends \PHPUnit\Framework\TestCase
{
    public function testFoo(bool $expectMatch): void
    {
        $string = 'keys=1000';

        $this->assertMatchesRegularExpression('/^keys=\d+/', $string);
        $this->assertSame($expectMatch ? 1 : 0, preg_match('/^keys=\d+/', $string));
        $this->assertDoesNotMatchRegularExpression('/^values=\d+/', $string);
    }
}

?>
