<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\CallLike\CreateStubOverCreateMockArgRector\Fixture;

use Rector\PHPUnit\Tests\PHPUnit120\Rector\CallLike\CreateStubOverCreateMockArgRector\Source\AbstractTestCaseWithItem;

final class SkipArgumentStoredInParentProperty extends AbstractTestCaseWithItem
{
    public function testThat()
    {
        $this->setUpItem($this->createMock(\stdClass::class));

        $this->item->expects($this->once())->method('someMethod');
    }

    public function testParentCall()
    {
        parent::setUpItem($this->createMock(\stdClass::class));

        $this->item->expects($this->once())->method('someMethod');
    }
}
