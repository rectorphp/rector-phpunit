<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\BehatPHPUnitAssertToWebmozzartRector\Fixture;

use Behat\Behat\Context\Context;
use PHPUnit\Framework\Assert;

final class SomeClass implements Context
{
    public function someDefinition()
    {
        Assert::assertSame('expected', 'given');

        Assert::assertStringContainsString('needle', 'haystack');
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\CodeQuality\Rector\ClassMethod\BehatPHPUnitAssertToWebmozzartRector\Fixture;

use Behat\Behat\Context\Context;
use PHPUnit\Framework\Assert;

final class SomeClass implements Context
{
    public function someDefinition()
    {
        \Webmozart\Assert\Assert::same('given', 'expected');

        \Webmozart\Assert\Assert::contains('needle', 'haystack');
    }
}

?>
