<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SiblingHelperNonAsserting extends TestCase
{
    public function testHelper()
    {
        $this->helper();
    }

    private function helper()
    {
        $value = 1;
    }
}

final class SiblingHelperAsserting extends TestCase
{
    public function testHelper()
    {
        $this->helper();
    }

    private function helper()
    {
        $this->assertTrue(true);
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

use PHPUnit\Framework\TestCase;

final class SiblingHelperNonAsserting extends TestCase
{
    #[\PHPUnit\Framework\Attributes\DoesNotPerformAssertions]
    public function testHelper()
    {
        $this->helper();
    }

    private function helper()
    {
        $value = 1;
    }
}

final class SiblingHelperAsserting extends TestCase
{
    public function testHelper()
    {
        $this->helper();
    }

    private function helper()
    {
        $this->assertTrue(true);
    }
}

?>
