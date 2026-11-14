<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

use PHPUnit\Framework\TestCase;

abstract class TraitParentNonAssertingBase extends TestCase
{
    protected function setUp(): void
    {
        $value = 1;
    }
}

trait TraitParentNonAssertingTrait
{
    protected function setUp(): void
    {
        parent::setUp();
    }
}

final class TraitParentNonAssertingTest extends TraitParentNonAssertingBase
{
    use TraitParentNonAssertingTrait;

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

abstract class TraitParentNonAssertingBase extends TestCase
{
    protected function setUp(): void
    {
        $value = 1;
    }
}

trait TraitParentNonAssertingTrait
{
    protected function setUp(): void
    {
        parent::setUp();
    }
}

final class TraitParentNonAssertingTest extends TraitParentNonAssertingBase
{
    use TraitParentNonAssertingTrait;

    #[\PHPUnit\Framework\Attributes\DoesNotPerformAssertions]
    public function testSomething()
    {
        $value = 1;
    }
}

?>
