<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

class TestInAnnotation extends \PHPUnit\Framework\TestCase
{
    /**
     * @test
     */
    public function thisIsTest()
    {
        $nothing = 5;
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

class TestInAnnotation extends \PHPUnit\Framework\TestCase
{
    /**
     * @test
     */
    #[\PHPUnit\Framework\Attributes\DoesNotPerformAssertions]
    public function thisIsTest()
    {
        $nothing = 5;
    }
}

?>
