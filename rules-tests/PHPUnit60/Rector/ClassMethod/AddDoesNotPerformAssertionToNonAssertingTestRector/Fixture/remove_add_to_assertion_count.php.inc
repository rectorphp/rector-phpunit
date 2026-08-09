<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

class RemoveAddToAssertionCount extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $this->someMethodCall();
        $this->addToAssertionCount(1);
    }

    private function someMethodCall()
    {
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

class RemoveAddToAssertionCount extends \PHPUnit\Framework\TestCase
{
    #[\PHPUnit\Framework\Attributes\DoesNotPerformAssertions]
    public function test()
    {
        $this->someMethodCall();
    }

    private function someMethodCall()
    {
    }
}

?>
