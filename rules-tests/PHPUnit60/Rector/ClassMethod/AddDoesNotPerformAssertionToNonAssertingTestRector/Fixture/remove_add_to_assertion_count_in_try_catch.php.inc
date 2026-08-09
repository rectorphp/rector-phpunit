<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

class RemoveAddToAssertionCountInTryCatch extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        try {
            $this->someMethodCall();
            $this->addToAssertionCount(1);
        } catch (\Throwable $throwable) {
        }
    }

    private function someMethodCall()
    {
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

class RemoveAddToAssertionCountInTryCatch extends \PHPUnit\Framework\TestCase
{
    #[\PHPUnit\Framework\Attributes\DoesNotPerformAssertions]
    public function test()
    {
        try {
            $this->someMethodCall();
        } catch (\Throwable $throwable) {
        }
    }

    private function someMethodCall()
    {
    }
}

?>
