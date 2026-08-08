<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

class RemoveAddToAssertionCountWithComment extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $this->someMethodCall();

        $this->addToAssertionCount(1); // Verify that no exception is thrown
    }

    private function someMethodCall()
    {
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

class RemoveAddToAssertionCountWithComment extends \PHPUnit\Framework\TestCase
{
    /**
     * @doesNotPerformAssertions
     */
    public function test()
    {
        $this->someMethodCall();
    }

    private function someMethodCall()
    {
    }
}

?>
