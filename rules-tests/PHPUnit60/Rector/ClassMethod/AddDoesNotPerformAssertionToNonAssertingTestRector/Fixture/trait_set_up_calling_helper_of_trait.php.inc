<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

use PHPUnit\Framework\TestCase;

trait TraitHelperNonAssertingTrait
{
    protected function setUp(): void
    {
        $this->check();
    }

    private function check(): void
    {
        $value = 1;
    }
}

trait TraitHelperAssertingTrait
{
    protected function setUp(): void
    {
        $this->check();
    }

    private function check(): void
    {
        $this->assertTrue(true);
    }
}

final class TraitHelperA extends TestCase
{
    use TraitHelperNonAssertingTrait;

    public function testA()
    {
        $value = 1;
    }
}

final class TraitHelperB extends TestCase
{
    use TraitHelperAssertingTrait;

    public function testB()
    {
        $value = 1;
    }
}
?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

use PHPUnit\Framework\TestCase;

trait TraitHelperNonAssertingTrait
{
    protected function setUp(): void
    {
        $this->check();
    }

    private function check(): void
    {
        $value = 1;
    }
}

trait TraitHelperAssertingTrait
{
    protected function setUp(): void
    {
        $this->check();
    }

    private function check(): void
    {
        $this->assertTrue(true);
    }
}

final class TraitHelperA extends TestCase
{
    use TraitHelperNonAssertingTrait;

    #[\PHPUnit\Framework\Attributes\DoesNotPerformAssertions]
    public function testA()
    {
        $value = 1;
    }
}

final class TraitHelperB extends TestCase
{
    use TraitHelperAssertingTrait;

    public function testB()
    {
        $value = 1;
    }
}
?>
