<?php

namespace Rector\PHPUnit\Tests\Rector\MethodCall\RemoveExpectAnyFromMockRector\Fixture;

use PHPUnit\Framework\TestCase;

final class KeepOnce extends TestCase
{
    public function test()
    {
        $translator = $this->createMock('Keep');
        $translator->expects($this->once())
            ->method('trans')
            ->willReturn('translated max {{ max }}!');
    }
}
