<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

use PHPUnit\Framework\TestCase;

class NonAssertingSetUp extends TestCase
{
    protected function setUp(): void
    {
        $this->value = 1;
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

use PHPUnit\Framework\TestCase;

class NonAssertingSetUp extends TestCase
{
    protected function setUp(): void
    {
        $this->value = 1;
    }

    #[\PHPUnit\Framework\Attributes\DoesNotPerformAssertions]
    public function testSomething()
    {
        $value = 5;
    }
}

?>
