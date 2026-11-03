<?php

namespace Rector\PHPUnit\Tests\PHPUnit90\Rector\MethodCall\AssertRegExpRector\Fixture;

final class NamedPregMatchArgs extends \PHPUnit\Framework\TestCase
{
    public function testFoo(): void
    {
        $string = 'keys=1000';

        $this->assertSame(1, preg_match(pattern: '/^keys=\d+/', subject: $string));
        $this->assertSame(0, preg_match(subject: $string, pattern: '/^values=\d+/'));
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit90\Rector\MethodCall\AssertRegExpRector\Fixture;

final class NamedPregMatchArgs extends \PHPUnit\Framework\TestCase
{
    public function testFoo(): void
    {
        $string = 'keys=1000';

        $this->assertMatchesRegularExpression(pattern: '/^keys=\d+/', string: $string);
        $this->assertDoesNotMatchRegularExpression(string: $string, pattern: '/^values=\d+/');
    }
}

?>
