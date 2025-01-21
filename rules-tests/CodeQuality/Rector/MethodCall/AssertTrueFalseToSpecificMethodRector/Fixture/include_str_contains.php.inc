<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertTrueFalseToSpecificMethodRector\Fixture;

final class IncludeStrContains extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $this->assertTrue(str_contains('haystack', 'needle'));

        $this->assertFalse(str_contains('haystack 2', 'needle 2'));
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\MethodCall\AssertTrueFalseToSpecificMethodRector\Fixture;

final class IncludeStrContains extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $this->assertStringContainsString('needle', 'haystack');

        $this->assertStringNotContainsString('needle 2', 'haystack 2');
    }
}

?>
