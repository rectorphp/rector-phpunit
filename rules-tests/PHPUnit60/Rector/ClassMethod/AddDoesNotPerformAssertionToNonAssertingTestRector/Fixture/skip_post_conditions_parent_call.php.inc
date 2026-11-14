<?php

namespace Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Fixture;

use Rector\PHPUnit\Tests\PHPUnit60\Rector\ClassMethod\AddDoesNotPerformAssertionToNonAssertingTestRector\Source\AbstractClassWithAssertingPostConditions;

class SkipPostConditionsParentCall extends AbstractClassWithAssertingPostConditions
{
    protected function assertPostConditions(): void
    {
        parent::assertPostConditions();
    }

    public function testSomething()
    {
        $value = 5;
    }
}
