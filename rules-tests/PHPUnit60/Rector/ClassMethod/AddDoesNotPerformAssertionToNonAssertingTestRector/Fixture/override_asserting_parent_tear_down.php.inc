<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

use Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Source\AbstractClassWithAssertingTearDown;

class OverrideAssertingParentTearDown extends AbstractClassWithAssertingTearDown
{
    protected function tearDown(): void
    {
        $this->value = null;
    }

    public function testSomething()
    {
        $value = 5;
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

use Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Source\AbstractClassWithAssertingTearDown;

class OverrideAssertingParentTearDown extends AbstractClassWithAssertingTearDown
{
    protected function tearDown(): void
    {
        $this->value = null;
    }

    #[\PHPUnit\Framework\Attributes\DoesNotPerformAssertions]
    public function testSomething()
    {
        $value = 5;
    }
}

?>
