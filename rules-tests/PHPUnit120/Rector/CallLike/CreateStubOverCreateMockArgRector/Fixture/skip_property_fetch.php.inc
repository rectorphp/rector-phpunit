<?php

namespace Rector\PHPUnit\Tests\PHPUnit120\Rector\CallLike\CreateStubOverCreateMockArgRector\Fixture;

use PHPUnit\Framework\MockObject\MockObject;
use PHPUnit\Framework\TestCase;

final class SkipPropertyFetch extends TestCase
{
    private MockObject $item;

    public function testThat()
    {
        $this->item = $this->createMock(\stdClass::class);
    }

    public function testUsedMock()
    {
        $this->item->expects($this->atLeastOnce())->method('someMethod')->willReturn(123);
    }
}
