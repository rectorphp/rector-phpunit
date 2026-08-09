<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

class SomeClass extends \PHPUnit\Framework\TestCase
{
    public function test()
    {
        $nothing = 5;
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

class SomeClass extends \PHPUnit\Framework\TestCase
{
    #[\PHPUnit\Framework\Attributes\DoesNotPerformAssertions]
    public function test()
    {
        $nothing = 5;
    }
}

?>
