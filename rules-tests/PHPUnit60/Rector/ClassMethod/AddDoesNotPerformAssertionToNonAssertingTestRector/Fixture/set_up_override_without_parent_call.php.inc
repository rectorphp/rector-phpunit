<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

use PHPUnit\Framework\TestCase;

abstract class ShadowBase extends TestCase
{
    protected function setUp(): void
    {
        $this->assertTrue(true);
    }
}

final class ShadowChild extends ShadowBase
{
    protected function setUp(): void
    {
        $value = 1;
    }

    public function testSomething()
    {
        $value = 1;
    }
}
?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

use PHPUnit\Framework\TestCase;

abstract class ShadowBase extends TestCase
{
    protected function setUp(): void
    {
        $this->assertTrue(true);
    }
}

final class ShadowChild extends ShadowBase
{
    protected function setUp(): void
    {
        $value = 1;
    }

    #[\PHPUnit\Framework\Attributes\DoesNotPerformAssertions]
    public function testSomething()
    {
        $value = 1;
    }
}
?>
