<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

class TestInAnnotatoin extends \PHPUnit\Framework\TestCase
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

class TestInAnnotatoin extends \PHPUnit\Framework\TestCase
{
    /**
     * @test
     * @doesNotPerformAssertions
     */
    public function thisIsTest()
    {
        $nothing = 5;
    }
}

?>
