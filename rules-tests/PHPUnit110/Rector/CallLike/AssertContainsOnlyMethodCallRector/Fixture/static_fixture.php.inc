<?php

namespace Rector\PHPUnit\Tests\PHPUnit110\Rector\CallLike\AssertContainsOnlyMethodCallRector\Fixture;

use PHPUnit\Framework\TestCase;

final class StaticFixture extends TestCase
{
    public function testMethod(): void
    {
        self::assertContainsOnly('string', ['a'], null, 'some message');
        self::assertContainsOnly('int', [1], true);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit110\Rector\CallLike\AssertContainsOnlyMethodCallRector\Fixture;

use PHPUnit\Framework\TestCase;

final class StaticFixture extends TestCase
{
    public function testMethod(): void
    {
        self::assertContainsOnlyString(['a'], 'some message');
        self::assertContainsOnlyInt([1]);
    }
}

?>
