<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertTrueFalseToSpecificMethodRector\Fixture;

use PHPUnit\Framework\Assert;

final class IncludeStrContains extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        Assert::assertTrue(str_contains('also', 'static'));

        $this->assertTrue(str_contains('haystack', 'needle'));
        $this->assertFalse(str_contains('haystack 2', 'needle 2'));
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertTrueFalseToSpecificMethodRector\Fixture;

use PHPUnit\Framework\Assert;

final class IncludeStrContains extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        Assert::assertStringContainsString('static', 'also');

        $this->assertStringContainsString('needle', 'haystack');
        $this->assertStringNotContainsString('needle 2', 'haystack 2');
    }
}

?>
