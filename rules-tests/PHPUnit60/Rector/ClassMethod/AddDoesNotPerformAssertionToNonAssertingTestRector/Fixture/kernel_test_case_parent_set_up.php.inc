<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

use Symfony\Bundle\FrameworkBundle\Test\WebTestCase;

final class KernelTestCaseParentSetUp extends WebTestCase
{
    protected function setUp(): void
    {
        parent::setUp();
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

use Symfony\Bundle\FrameworkBundle\Test\WebTestCase;

final class KernelTestCaseParentSetUp extends WebTestCase
{
    protected function setUp(): void
    {
        parent::setUp();
    }

    #[\PHPUnit\Framework\Attributes\DoesNotPerformAssertions]
    public function testSomething()
    {
        $value = 1;
    }
}

?>
