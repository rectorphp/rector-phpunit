<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

class TestInAnnotationWithTestAttribute extends \PHPUnit\Framework\TestCase
{
    #[\PHPUnit\Framework\Attributes\Test]
    public function thisIsTest()
    {
        $nothing = 5;
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

class TestInAnnotationWithTestAttribute extends \PHPUnit\Framework\TestCase
{
    /**
     * @doesNotPerformAssertions
     */
    #[\PHPUnit\Framework\Attributes\Test]
    public function thisIsTest()
    {
        $nothing = 5;
    }
}

?>
