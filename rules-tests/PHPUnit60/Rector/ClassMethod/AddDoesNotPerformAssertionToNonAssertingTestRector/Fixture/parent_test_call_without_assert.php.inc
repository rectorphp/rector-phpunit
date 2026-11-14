<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

use Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Source\AbstractClassWithNonAssertingMethod;

class ParentTestCallWithoutAssert extends AbstractClassWithNonAssertingMethod
{
    public function testSomething()
    {
        parent::testSomething();
    }
}

?>
-----
<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

use Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Source\AbstractClassWithNonAssertingMethod;

class ParentTestCallWithoutAssert extends AbstractClassWithNonAssertingMethod
{
    #[\PHPUnit\Framework\Attributes\DoesNotPerformAssertions]
    public function testSomething()
    {
        parent::testSomething();
    }
}

?>
